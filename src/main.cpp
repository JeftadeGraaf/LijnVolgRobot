#include <Arduino.h>
#include <Display.h>
#include <IRSensor.h>
#include <IRArray.h>
#include <MotorController.h>
#include <NewPing.h>

long int startMillis;

char getLastTwoDigitsChar(int number, int position) {
  // Convert the number to a string
  String numberString = String(number);
  
  // Get the length of the string
  int length = numberString.length();

  // Calculate the position from the end of the string
  int charPosition = length - position;

  // Check if the position is valid
  if (charPosition >= 0 && charPosition < length) {
    return numberString.charAt(charPosition);
  } else {
    return '0'; // Return '0' if position is out of range
  }
}
// put function declarations here:
int digitPins[7] = {17, 16, 15, 14, 2, 1, 0};
Display display(digitPins, 18, 19);
MotorController motorcontroller(12, 3, 13, 11);

int IRArrayPins[5] = {8,7,6,5,4};

int directionPinRechts = 12; // right, low = vooruit
int pwmPinRechts = 3;
int directionPinLinks = 13; // left, high = vooruit
int pwmPinLinks = 11;
int dotPin = 10;
int triggerPin = 9;

int rechts_vooruit = 0;
int rechts_achteruit = 1;
int links_vooruit = 1;
int links_achteruit = 0;

//boolean to switch direction
bool directionState;
bool driving = true;


IRArray irArray(IRArrayPins);
NewPing sonar(triggerPin, triggerPin, 10);

void setup(){
  TCCR2B = TCCR2B & B11111000 | B00000111;
  //define pins
  display.setup();
  motorcontroller.setup();
  irArray.setup();
  pinMode(dotPin, OUTPUT);
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
  // Moves the robot slightly forward
  motorcontroller.moveForward();
  startMillis = millis();
  while(millis() - startMillis < 350) {
    display.displayTime();
  }
  motorcontroller.stop();
  startMillis = millis();
  while(millis() - startMillis < 250) {
    display.displayTime();
  }
  irArray.refreshValues();
  if (irArray.values[0] == 0 && irArray.values[1] == 0 && irArray.values[2] == 0 && irArray.values[3] == 0 && irArray.values[4] == 0) {
    // driving = false;
    return true;
  }
  // returns the robot to starting position
  motorcontroller.moveBackward();
  startMillis = millis();
  while(millis() - startMillis < 350) {
    display.displayTime();
  }
  motorcontroller.stop();
  return false;
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
      digitalWrite(dotPin, HIGH);
      //delay(1000);
      digitalWrite(directionPinLinks, links_vooruit);
      digitalWrite(directionPinRechts, rechts_achteruit);
      analogWrite(pwmPinLinks, 50);
      analogWrite(pwmPinRechts, 50);

      long int startMillis = millis();
      while(millis() - startMillis <= 500) {
      display.displayTime();
      }
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
    motorcontroller.smallLeft();

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
    motorcontroller.bigLeft(display);

  }

  else if (bitvalue == "10000"){
    motorcontroller.bigRight(display);
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
    motorcontroller.smallLeft();

  }

  else if (bitvalue == "11000"){
    motorcontroller.bigRight(display);

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
    motorcontroller.bigRight(display);
  }

  else if (bitvalue == "11111"){
  
    digitalWrite(directionPinLinks, links_achteruit);
    digitalWrite(directionPinRechts, rechts_vooruit);
    analogWrite(pwmPinLinks, 50);
    analogWrite(pwmPinRechts, 50);
  }
}

void loop(){
  display.aftellen('1', '0');
  display.setStartTime();
  irArray.refreshValues();

  while(irArray.values[0] != 0 && irArray.values[1] != 0 && irArray.values[2] != 0 && irArray.values[3] != 0 && irArray.values[4] != 0) {
    motorcontroller.moveForward();
    irArray.refreshValues();
    display.displayTime();
  }

  while (driving) {
    irArray.refreshValues();
    digitalWrite(dotPin, LOW);
    getMovement();
    if(sonar.ping_cm() != 0) {
      motorcontroller.turnAround(display);
    }
    display.displayTime();
    digitalWrite(dotPin, LOW);
  }
  display.displayFinishTime();
}