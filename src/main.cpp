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
}

void searchDirection() {
  
  while (irArray.values[0] == 1 || irArray.values[1] == 1 || irArray.values[2] == 1 || irArray.values[3] == 1 || irArray.values[4] == 1) {
  digitalWrite(directionPinLinks, links_achteruit);
  digitalWrite(directionPinRechts, rechts_vooruit);
  analogWrite(pwmPinLinks, 50);
  analogWrite(pwmPinRechts, 50);
  irArray.refreshValues();
  }
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, links_vooruit);

  irArray.refreshValues();

}

bool checkFinish() {
  bool intersection;
    
  // Moves the robot slightly forward
  motorcontroller.moveForward();
  delay(350);
  motorcontroller.stop();
  delay(250);
  irArray.refreshValues();
  if ((irArray.values[0] == 1 || irArray.values[4] == 1) && (irArray.values[1] == 0 || irArray.values[2] == 0 || irArray.values[3] == 0) ) {
    intersection = false;
  }
  else if (irArray.values[0] == 0 && irArray.values[1] == 0 && irArray.values[2] == 0 && irArray.values[3] == 0 && irArray.values[4] == 0) {
    driving = false;
    intersection = true;
  }
  // returns the robot to starting position
  motorcontroller.moveBackward();
  delay(350);
  motorcontroller.stop();
  return intersection;
}

void driveToStart {
  irArray.refreshValues();
  while (irArray.values[0] != 0 || irArray.values[1] != 0 || irArray.values[2] != 0 || irArray.values[3] != 0 || irArray.values[4] != 0) {
    irArray.refreshValues();
    motorcontroller.moveForward();
  }
}

void getMovement() {
 
  String bitvalue = "";

  for (int i = 0; i < 5; i++) {
      bitvalue += String(irArray.values[i]);
  }



  if (bitvalue == "00000") {
    // motorcontroller.moveForward();
    if (checkFinish()) { 
      driving = false;
    }
    else {
      digitalWrite(directionPinLinks, links_achteruit);
      digitalWrite(directionPinRechts, rechts_vooruit);
      analogWrite(pwmPinLinks, 50);
      analogWrite(pwmPinRechts, 50);
      delay(500);
    }
  }
  else if (bitvalue == "00001"){
    motorcontroller.moveForward();
    
  }

  else if (bitvalue == "00010"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "00011"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "00100"){
    motorcontroller.moveForward();


  }

  else if (bitvalue == "00101"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "00110"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "00111"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01000"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01001"){

  }

  else if (bitvalue == "01010"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01011"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01100"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01101"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01110"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "01111"){
    motorcontroller.bigLeft();

  }

  else if (bitvalue == "10000"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10001"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10010"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10011"){
    motorcontroller.smallLeft();

  }

  else if (bitvalue == "10100"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10101"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10110"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "10111"){
    motorcontroller.smallRight();

  }

  else if (bitvalue == "11000"){
    irArray.refreshValues();
    while (irArray.values[4] == 0) {
      motorcontroller.bigRight();
      irArray.refreshValues();
    }

  }

  else if (bitvalue == "11001"){
    motorcontroller.smallRight();

  }

  else if (bitvalue == "11010"){

  }

  else if (bitvalue == "11011"){
    motorcontroller.moveForward();

  }

  else if (bitvalue == "11100"){
    motorcontroller.smallRight();

  }

  else if (bitvalue == "11101"){
    motorcontroller.smallRight();

  }

  else if (bitvalue == "11110"){
    motorcontroller.bigRight();
  }

  else if (bitvalue == "11111"){
  
    digitalWrite(directionPinLinks, links_achteruit);
    digitalWrite(directionPinRechts, rechts_vooruit);
    analogWrite(pwmPinLinks, 50);
    analogWrite(pwmPinRechts, 50);
  }
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