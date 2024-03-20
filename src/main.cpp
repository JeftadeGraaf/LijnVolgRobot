#include <Arduino.h>
#include <Display.h>
#include <IRSensor.h>
#include <IRArray.h>
#include <USSensor.h>
#include <MotorController.h>


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
int echoPin = 10;
int triggerPin = 9;

int rechts_vooruit = 0;
int rechts_achteruit = 1;
int links_vooruit = 1;
int links_achteruit = 0;

//boolean to switch direction
bool directionState;
bool driving = true;


IRArray irArray(IRArrayPins);
USSensor usSensor(triggerPin, echoPin);

void setup(){
  TCCR2B = TCCR2B & B11111000 | B00000111;
  //define pins
  display.setup();
  motorcontroller.setup();
  irArray.setup();
  usSensor.setup();
}

// Turns the robot 180 degrees
void turnAround() {
  digitalWrite(directionPinLinks, links_achteruit);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  delay(500);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, links_vooruit);
  delay(1000);
}

// Checks if all sensors are displaying black
String checkFinish() {
  motorcontroller.stop();
  // Moves the robot slightly forward
  motorcontroller.moveForward();
  delay(500);
  motorcontroller.stop();
  delay(200);
  irArray.refreshValues();
  if ((irArray.values[0] == 1 || irArray.values[4] == 1) && (irArray.values[1] == 0 || irArray.values[2] == 0 || irArray.values[3] == 0) ) {
    return "straight";
  }
  else if (irArray.values[0] == 0 && irArray.values[1] == 0 && irArray.values[2] == 0 && irArray.values[3] == 0 && irArray.values[4] == 0) {
    driving = false;
    return "finish";
  }
  // Moves the robot slightly backwards to it's starting position
  motorcontroller.moveBackward();
  //delay(00);
  motorcontroller.stop();
  return "turn";
}

// Checks if there is a straight path available or if the robot is on the finish line
// bool checkIntersection() {
//     bool i;
    
//     // Moves the robot slightly forward
//     analogWrite(pwmPinRechts, 100);
//     analogWrite(pwmPinLinks, 100);
//     delay(250);
//     analogWrite(pwmPinRechts, 0);
//     analogWrite(pwmPinLinks, 0);
//     // Checks if there is a straight path or if the robot is on the finish line
//     if (irArray.values[2] == 0) {
//       i = true;
//     } else {
//       i = false;
//     }
//     // Moves the robot slightly backwards to it's starting position
//     digitalWrite(directionPinRechts, rechts_achteruit);
//     digitalWrite(directionPinLinks, links_achteruit);
//     analogWrite(pwmPinRechts, 100);
//     analogWrite(pwmPinLinks, 100);
//     delay(250);
//     analogWrite(pwmPinRechts, 0);
//     analogWrite(pwmPinLinks, 0);
//     // Resets the robot motors
//     digitalWrite(directionPinRechts, rechts_vooruit);
//     digitalWrite(directionPinLinks, links_vooruit);

//     return i;
// }

void checkForObstacle() {
  if (usSensor.getDistance() < 10) {
    turnAround();
  }
}

void turnLeft() {
  digitalWrite(directionPinLinks, links_achteruit);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  delay(250);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, links_vooruit);
}

void turnRight() {
  // analogWrite(pwmPinLinks, 75);
  // analogWrite(pwmPinRechts, 75);
  // delay(150);
  digitalWrite(directionPinRechts, rechts_achteruit);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  delay(300);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, rechts_vooruit);
  delay(1000);
}

void getMovement() {
 
  String bitvalue = "";

  for (int i = 0; i < 5; i++) {
      bitvalue += String(irArray.values[i]);
  }



  if (bitvalue == "00000") {
    if (checkFinish() == "turn") {
      turnRight();
    }
  }
  else if (bitvalue == "00001"){
    motorcontroller.stop();
    delay(1000);
    String state = checkFinish();
    if (state == "straight") {
      motorcontroller.moveForward();
    } else {
      
      turnLeft();
      while (irArray.values[0] == 1){
      irArray.refreshValues();
      motorcontroller.moveForward();
      }

  	  motorcontroller.stop();
      delay (100);

      while (irArray.values[0] == 0){
      irArray.refreshValues();
      motorcontroller.bigLeft();
      }
    }
  }

  else if (bitvalue == "00010"){
    motorcontroller.smallRight();
  }

  else if (bitvalue == "00011"){
    motorcontroller.stop();
    delay(1000);
    String state = checkFinish();
    if (state == "straight") {
      motorcontroller.moveForward();
    } else {
      
      turnLeft();
      while (irArray.values[0] == 1){
      irArray.refreshValues();
      motorcontroller.moveForward();
      }

  	  motorcontroller.stop();
      delay (100);

      while (irArray.values[0] == 0){
      irArray.refreshValues();
      motorcontroller.bigLeft();
      }
    }
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
    motorcontroller.counter = 0;
  }

  else if (bitvalue == "01000"){
    motorcontroller.smallLeft();
  }

  else if (bitvalue == "01001"){
    motorcontroller.moveForward();
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
    delay(250);
  }

  else if (bitvalue == "10000"){
    motorcontroller.bigRight();
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
    while (irArray.values[4] == 0){
      irArray.refreshValues();
      motorcontroller.bigRight();
    }
    // motorcontroller.bigRight();
    // motorcontroller.counter = 0;
    // delay(700);
    // motorcontroller.stop();
  }

  else if (bitvalue == "11001"){
    motorcontroller.smallRight();
  }

  else if (bitvalue == "11010"){
    motorcontroller.moveForward();
  }

  else if (bitvalue == "11011"){
    motorcontroller.moveForward();
    motorcontroller.counter = 0;
  }

  else if (bitvalue == "11100"){
    motorcontroller.smallRight();
    motorcontroller.counter = 0;
  }

  else if (bitvalue == "11101"){
    motorcontroller.smallRight();
  }

  else if (bitvalue == "11110"){
    motorcontroller.bigRight();
    delay(250);
  }

  else if (bitvalue == "11111"){
    char digit_1 = getLastTwoDigitsChar(motorcontroller.counter, 1);
    char digit_2 = getLastTwoDigitsChar(motorcontroller.counter, 2);
    display.setCharacters(digit_2, digit_1);
    display.displayCharacters();

    if(motorcontroller.counter > 30){


    motorcontroller.counter = 0;
    motorcontroller.turnAround();
    
    
    } else {
      motorcontroller.counter++;
    }
  }

}



void loop(){
    irArray.refreshValues();
    getMovement();
}