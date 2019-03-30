/*
   Author: Maalv
   Wilco Version 0.1
   Date: 3/30/19, 4:09 PM @AMRoC For TDT
*/
#include <Servo.h>

Servo rightServo;
Servo leftServo;
  
//SERVO MAX = 150

int redStrobePin = A5;
int strongbackLEDPin = A4;
int piezoPin = 8;
int igniteButtonPin = 7;
int piezoFreq = 750;
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 11;
int g = 12;

void setServos() {
  rightServo.attach(9);
  rightServo.write(180);
  delay(1000);
  rightServo.detach();
  leftServo.attach(10);
  leftServo.write(0);
  delay(1000);
  leftServo.detach();
}

void moveRightServo(int pos, int rate, long delayTime) {
  rightServo.attach(9);
  for (int i = 180; i > pos; i -= rate) {
    rightServo.write(i);
    delay(delayTime);
  }
  rightServo.detach();
}

void moveLeftServo(int pos, int rate, long delayTime) {
  leftServo.attach(10);
  for (int i = 0; i < pos; i += rate) {
    leftServo.write(i);
    delay(delayTime);
  }
  leftServo.detach();
}

void testServos() {
  setServos();
  delay(500);
  moveRightServo(40, 20, 50);
  delay(500);
  moveLeftServo(140, 20, 50);
  delay(500);
//  setServos();
}
void startup() {
  for (int i = 0; i < 3; i++) strobe();
  flashAllStrongback(500, 3);
  testPiezo();
  delay(1500);
  tone(piezoPin, piezoFreq, 250);
  delay(250);
  noTone(piezoPin);
  delay(250);
  tone(piezoPin, piezoFreq, 250);
  delay(500);
  noTone(piezoPin);
  delay(500);
  testServos();
  delay(1000);
  digitalWrite(redStrobePin, HIGH);
  delay(1000);
  allStrongback(true);
  delay(1000);
//  allStrongback(false);
//  digitalWrite(redStrobePin, LOW);
  setServos();
  delay(1500);
  showNumber(8);
  delay(2500);
  showNumber(-1);
  delay(1000);
  digitalWrite(g, HIGH);
  for (int i = 0; i < 3; i++) {
    delay(125);
    tone(piezoPin, piezoFreq, 125);
    delay(125);
  }
}

void strobe() {
  digitalWrite(redStrobePin, HIGH);
  delay(1000);
  digitalWrite(redStrobePin, LOW);
  delay(1000);
}

void padIdle() {
  allStrongback(true);
  while (!getButtonState()) strobe();
}

void allStrongback(bool state) {
  if (state) digitalWrite(strongbackLEDPin, HIGH);
  else digitalWrite(strongbackLEDPin, LOW);
}

void flashAllStrongback(long time) { //In milliseconds
  digitalWrite(strongbackLEDPin, HIGH);
  delay(time);
  digitalWrite(strongbackLEDPin, LOW);
  delay(time);
}


void flashAllStrongback(long time, int iterations) { //In milliseconds, number of times to flash
  for (int i = 0; i < iterations; i++) {
    digitalWrite(strongbackLEDPin, HIGH);
    delay(time);
    digitalWrite(strongbackLEDPin, LOW);
    delay(time);
  }
}

void testPiezo() {
  tone(piezoPin, piezoFreq, 1000);
}

void terminalCount() { //IF SERVOS CANT MOVe,  STOP - USE SERVO.READ?
  for (int i = 0; i <= 15; i++) {
     showNumber(15 - i);
     if (i == 9) moveLeftServo(60, 20, 150);
     if (i == 8) moveLeftServo(120, 20, 150);
    }
    digitalWrite(redStrobePin, HIGH);
    digitalWrite(strongbackLEDPin, HIGH);
    delay(250);
    tone(piezoPin, piezoFreq, 250); //(pin, frequency, time)
    delay(500);
    digitalWrite(redStrobePin, LOW);
    digitalWrite(strongbackLEDPin, LOW);
    noTone(piezoPin);
    delay(500);
  }
  ignite();
  flashAllStrongback(125, 5);
}

void postLaunch() {
  allStrongback(true);
  delay(5000);
  allStrongback(false);
  for (int i = 0; i < 300; i++) strobe();
}

void ignite() {
  //TODO: IGNITE STARTER CODE HERE!
}

void showNumber(int number) {
  switch (number) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 10: //A
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 11: //B
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 12: //C
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 13: //D
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 14: //E
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 15: //F
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    default: //All off
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  }
}

bool getButtonState() {
  bool buttonstate = (bool) digitalRead(igniteButtonPin);
  return !buttonstate;
}
void setup() {
  pinMode(redStrobePin, OUTPUT);
  pinMode(strongbackLEDPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(igniteButtonPin, INPUT);
  digitalWrite(igniteButtonPin, HIGH);
  Serial.begin(9600);
  
}
// EW, PRAYUJ - 3-19-19 (in response to him saying "Ew, Arduino") when i sent him snap of my code
void loop() {
  startup();
  padIdle();
  terminalCount();
  postLaunch();
  while(true) { }
}

