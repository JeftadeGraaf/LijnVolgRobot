#include <Arduino.h>
#include <Display.h>
#include <IRSensor.h>
#include <IRArray.h>
#include <USSensor.h>

// put function declarations here:
int digitPins[7] = {17, 16, 15, 14, 2, 1, 0};
Display display(digitPins, 18, 19);

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


IRArray irArray(IRArrayPins);
USSensor usSensor(triggerPin, echoPin);

void setup(){
  //define pins
  display.setup();
  pinMode(directionPinRechts, OUTPUT); // right motor
  pinMode(pwmPinRechts, OUTPUT);
  pinMode(directionPinLinks, OUTPUT); // left motor
  pinMode(pwmPinLinks, OUTPUT);
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
bool checkFinish() {
  // Moves the robot slightly forward
  analogWrite(pwmPinRechts, 100);
  analogWrite(pwmPinLinks, 100);
  delay(250);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  for (int i; i < 5; i++) {
    if (irArray.values[i] == 1) {
      // Moves the robot slightly backwards to it's starting position
      digitalWrite(directionPinRechts, HIGH);
      digitalWrite(directionPinLinks, LOW);
      analogWrite(pwmPinRechts, 100);
      analogWrite(pwmPinLinks, 100);
      delay(250);
      analogWrite(pwmPinRechts, 0);
      analogWrite(pwmPinLinks, 0);
      // Resets the robot motors
      digitalWrite(directionPinLinks, LOW);
      digitalWrite(directionPinLinks, HIGH);
      return false;
    }  
  }
  // Moves the robot slightly backwards to it's starting position
  digitalWrite(directionPinRechts, LOW);
  digitalWrite(directionPinLinks, HIGH);
  analogWrite(pwmPinRechts, 50);
  analogWrite(pwmPinLinks, 50);
  delay(10000);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  // Resets the robot motors
  digitalWrite(directionPinLinks, HIGH);
  digitalWrite(directionPinLinks, LOW);
  return true;
}

// Checks if there is a straight path available or if the robot is on the finish line
bool checkIntersection() {
    bool i;
    
    // Moves the robot slightly forward
    analogWrite(pwmPinRechts, 50);
    analogWrite(pwmPinLinks, 50);
    delay(250);
    analogWrite(pwmPinRechts, 0);
    analogWrite(pwmPinLinks, 0);
    // Checks if there is a straight path or if the robot is on the finish line
    if (irArray.values[2] == 0) {
      i = true;
    } else {
      i = false;
    }
    // Moves the robot slightly backwards to it's starting position
    digitalWrite(directionPinRechts, LOW);
    digitalWrite(directionPinLinks, HIGH);
    analogWrite(pwmPinRechts, 50);
    analogWrite(pwmPinLinks, 50);
    delay(250);
    analogWrite(pwmPinRechts, 0);
    analogWrite(pwmPinLinks, 0);
    // Resets the robot motors
    digitalWrite(directionPinLinks, HIGH);
    digitalWrite(directionPinLinks, LOW);

    return i;
}

void checkForObstacle() {
  if (usSensor.getDistance() < 10) {
    turnAround();
  }
}

void turnLeft() {
  digitalWrite(directionPinLinks, LOW);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  delay(300);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, HIGH);
  delay(1000);
}

void turnRight() {
  digitalWrite(directionPinRechts, LOW);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  delay(300);
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, HIGH);
  delay(1000);
}

void getMovement(int arrayValues[5]) {
  char bitvalue[5];
  for (int i = 0; i < 5; ++i) {
    bitvalue[i] = arrayValues[i];
  }

  //motor values
  int arraytinyright[4] = {70, 1, 55, 1};
  int arraybigright[4] = {80, 1, 30, 1};
  int arrayahead[4] = {100, 1, 100, 1};
  int arraytinyleft[4] = {70, 1, 55, 1};
  int arraybigleft[4] = {80, 1, 30, 1};

  if (bitvalue == "00000") {
    if (checkFinish()) {
      // Stop het hele programma en laat finishtijd zien
    }
    else {
      turnLeft();
    }
  }
  else if (bitvalue == "00001"){
    //case 1
  }

  else if (bitvalue == "00010"){
    //case 2
  }

  else if (bitvalue == "00011"){
    //case 3
  }

  else if (bitvalue == "00100"){
    //case 4
  }

  else if (bitvalue == "00101"){
    //case 5
  }

  else if (bitvalue == "00110"){
    //case 6
  }

  else if (bitvalue == "00111"){
    //case 7
  }

  else if (bitvalue == "01000"){
    //case 8
  }

  else if (bitvalue == "01001"){
    //case 9
  }

  else if (bitvalue == "01010"){
    //case 10
  }

  else if (bitvalue == "01011"){
    //case 11
  }

  else if (bitvalue == "01100"){
    //case 12
  }

  else if (bitvalue == "01101"){
    //case 13
  }

  else if (bitvalue == "01110"){
    //case 14
  }

  else if (bitvalue == "01111"){
    digitalWrite(directionPinRechts, rechts_vooruit);
    analogWrite(directionPinLinks, arraytinyright[0]);
  }

  else if (bitvalue == "10000"){
    //case 16
  }

  else if (bitvalue == "10001"){
    //case 17
  }

  else if (bitvalue == "10010"){
    //case 18
  }

  else if (bitvalue == "10011"){
    //case 19
  }

  else if (bitvalue == "10100"){
    //case 20
  }

  else if (bitvalue == "10101"){
    //case 21
  }

  else if (bitvalue == "10110"){
    //case 22
  }

  else if (bitvalue == "10111"){
    //case 23
  }

  else if (bitvalue == "11000"){
    //case 24
  }

  else if (bitvalue == "11001"){
    //case 25
  }

  else if (bitvalue == "11010"){
    //case 26
  }

  else if (bitvalue == "11011"){
    //case 27
  }

  else if (bitvalue == "11100"){
    //case 28
  }

  else if (bitvalue == "11101"){
    //case 29
  }

  else if (bitvalue == "11110"){
    //case 30
  }

  else if (bitvalue == "11111"){
    //case 31
  }

}



void loop(){
  digitalWrite(directionPinRechts, rechts_achteruit);
  analogWrite(pwmPinRechts, 255);
  delay(1000);
  analogWrite(pwmPinRechts, 0);

}