/*
   Author: Maalv
   Soar Version 0.0
   Date: 3/31/19, 6:26 PM
*/
#include <Wire.h>
#include <SFE_BMP180.h>
#include <SD.h>
#include <SPI.h>

File file;
SFE_BMP180 bmp180;
float Po = 1020.0;
char status;
double T, P, alt;
double baselineAlt;
int redPin = 6;
int greenPin = 7;
int bluePin = 8;
int piezoPin = 5;
int piezoFreq = 750;

double calcPressure(double T) {
  status = bmp180.startPressure(3);
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed pressure measurement:
    // Note that the measurement is stored in the variable P.
    // Note also thatt the function requires the previous temperature measurement (T).
    // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
    // Function returns 1 if successful, 0 if failure.

    status = bmp180.getPressure(P, T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("absolute pressure: ");
      Serial.print(P, 2);
      Serial.print(" mb, ");
      Serial.print(P * 0.0295333727, 2);
      Serial.println(" inHg");
    }
  }
  return P;
}
double calcTemp() {
  status = bmp180.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = bmp180.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      //      Serial.print("temperature: ");
      //      Serial.print(T, 2);
      //      Serial.print(" deg C, ");
      //      Serial.print((9.0 / 5.0)*T + 32.0, 2);
      //      Serial.println(" deg F");
    }
  }
  return T;
}
double calcAltitude() {
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    delay(500);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          alt = bmp180.altitude(P, Po);
          alt = alt / 0.3048;
          Serial.print("Altitude: ");
          Serial.print(alt);
          Serial.println(" FT");
        }
      }
    }
  }
  return alt;
}

double baselineAltitude() {
  double baseline;
  setColor(102, 0, 204);
  for (int i = 0; i < 5; i++) {
    double curalt = calcAltitude();
    baseline += curalt;
    delay(1000);
  }
  baseline /= 5;
  setColor(0, 0, 0); //If purple, baseline altitude measuring - aded on 5 26 19 @ 8:59pm @ Jay's house
  return baseline;
}

void setColor(int red, int green, int blue)
{
  //#ifdef COMMON_ANODE
//  red = 255 - red;
//  green = 255 - green;
//  blue = 255 - blue;
  //#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void flashLoop(int r, int g, int b, int delayTime, int num) {
  for (int i = 0; i < num; i++) {
    setColor(r, g, b);
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);
  }
}

void buzz(int buzzTime, int repetitions) {
  for (int i = 0; i < repetitions; i++) {
    tone(piezoPin, piezoFreq, buzzTime);
    delay(buzzTime);
    noTone(piezoPin);
    delay(buzzTime);
  }
}

void startup() {
  setColor(255, 0, 0);
  delay(750);
  setColor(0, 255, 0);
  delay(750);
  setColor(0, 0, 255);
  delay(750);
  setColor(0, 0, 0);
  delay(750);
  //buzzer stuff
  buzz(500, 1);
}

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(10, OUTPUT); //Cs Pin
  startup();
  Serial.println("inited");
  bool success = bmp180.begin();
  if (success) {
    Serial.println("BMP180 init success");
    flashLoop(0, 255, 0, 500, 3); //If flashing green, baromeer good
  } else {
    while (true) {
      setColor(0, 255, 0); //TODO: MAKE ERROR CODE SHEET W/ COLORS AND DESCRIPTIONS
      buzz(250, 5);
    }
  }
  delay(1000);
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
    flashLoop(255, 0, 0, 500, 3);
  } else {
    Serial.println("SD card initialization failed");
    while (true) {
      setColor(255, 0, 0);
      buzz(250, 5);
    }
    //    return;
  } //if flashing blue sd card good
  baselineAlt = baselineAltitude();
  Serial.print("Baseline Altitude: ");
  Serial.println(baselineAlt);
  Serial.println();
  Serial.println();
  SD.remove("ALTITUDE.TXT");
  File alt = SD.open("Altitude.txt", FILE_WRITE);
  alt.print("Baseline altitude measured: ");
  alt.println(baselineAlt);
  alt.println();
  alt.println("time, currentAlt, currentCalAlt, currentTempF, currentPressureMb");
  alt.close();
  setColor(102, 153, 255); //good startup
  buzz(250, 3);
}

void loop() {
  //code to flash till litoff detected or gets signal from pad?
  double currentAlt = calcAltitude();
  double currentCalAlt = currentAlt - baselineAlt;
  double currentTempC = calcTemp();
  double currentTempF = (9.0 / 5.0) * calcTemp() + 32.0;
  double currentPressureMb = calcPressure(currentTempC);
  //  double currentPressureInHg = currentPressureMb * 0.0295333727;
  String comma = String ("    ,   ");
  File alt = SD.open("Altitude.txt", FILE_WRITE);
  if (alt) {
    Serial.println("printing to card");
    Serial.print("altitude: ");
    Serial.println(currentAlt);
    Serial.print("cal altitude: ");
    Serial.println(currentCalAlt);
    alt.println(millis() + comma + currentAlt + comma + currentCalAlt + comma + currentTempF + comma + currentPressureMb);
    alt.close();
  }
  else { 
    Serial.println("ERROR");
    while(!alt) {
      flashLoop(255, 0, 0, 500, 3);
      setColor(255, 0, 0);
      buzz(500, 3);
      setColor(0, 0, 0); //Beeping and flashing red means cannot write to SD card :( - added 5-26-19 @8:57pm @ Jay's housed
    }
  }
}
