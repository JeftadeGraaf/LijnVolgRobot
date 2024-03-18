#include <Arduino.h>
#include <Display.h>
#include <IRSensor.h>
#include <IRArray.h>
#include <USSensor.h>

// put function declarations here:
int digitPins[7] = {17, 16, 15, 14, 2, 1, 0};
Display display(digitPins, 18, 19);

int IRArrayPins[5] = {4,5,6,7,8};

int directionPinA = 12;
int pwmPinA = 3;
int directionPinB = 13;
int pwmPinB = 11;
int echoPin = 10;
int triggerPin = 9;

//boolean to switch direction
bool directionState;

IRArray irArray(IRArrayPins);
USSensor usSensor(triggerPin, echoPin);

void setup(){
  //define pins
  display.setup();
  pinMode(directionPinA, OUTPUT); // right motor
  pinMode(pwmPinA, OUTPUT);
  pinMode(directionPinB, OUTPUT); // left motor
  pinMode(pwmPinB, OUTPUT);
  irArray.setup();
  usSensor.setup();
  Serial.begin(9600);
}

void turnAround() {
  digitalWrite(directionPinB, LOW);
  analogWrite(pwmPinB, 100);
  analogWrite(pwmPinA, 100);
  delay(500);
  analogWrite(pwmPinA, 0);
  analogWrite(pwmPinB, 0);
  digitalWrite(directionPinB, HIGH);
  delay(1000);
}

void loop(){
  irArray.refreshValues();
  digitalWrite(directionPinA, LOW);
  digitalWrite(directionPinB, HIGH);
  //set work duty for the motor
  turnAround();
  // if (irArray.values[2] == 0) {
  //   analogWrite(pwmPinA, 100);
  //   analogWrite(pwmPinB, 100);
  // } else if (irArray.values[1] == 1) {
  //   analogWrite(pwmPinA, 50);
  //   analogWrite(pwmPinB, 25);
  // } else if (irArray.values[3] == 1) {
  //   analogWrite(pwmPinA, 25);
  //   analogWrite(pwmPinB, 50);
  // } else {
  //   analogWrite(pwmPinA, 0);
  //   analogWrite(pwmPinB, 0);
  // }
  display.displayChar('F');
}