#include "Arduino.h"
#include "MotorController.h"
#include <Display.h>

MotorController::MotorController(int directionPinRechts, int pwmPinRechts, int directionPinLinks, int pwmPinLinks) {
    // Constructor
    MotorController::directionPinRechts = directionPinRechts;
    MotorController::pwmPinRechts = pwmPinRechts;
    MotorController::directionPinLinks = directionPinLinks;
    MotorController::pwmPinLinks = pwmPinLinks;
}

void MotorController::setup() {
    // Add your implementation here
    pinMode(directionPinRechts, OUTPUT); // right motor
    pinMode(pwmPinRechts, OUTPUT);
    pinMode(directionPinLinks, OUTPUT); // left motor
    pinMode(pwmPinLinks, OUTPUT);
}

void MotorController::degrees90Left(Display display) {

    digitalWrite(directionPinLinks, links_achteruit);
    analogWrite(pwmPinLinks, 100);
    analogWrite(pwmPinRechts, 100);
    startMillis = millis();
    while(millis() - startMillis < 300) {
        display.displayTime();
    }
    analogWrite(pwmPinRechts, 0);
    analogWrite(pwmPinLinks, 0);
    digitalWrite(directionPinLinks, links_vooruit);
    startMillis = millis();
    while(millis() - startMillis < 200) {
        display.displayTime();
    }
        
}

void MotorController::degrees90Right(Display display) {

    digitalWrite(directionPinRechts, rechts_achteruit);
    analogWrite(pwmPinRechts, 100);
    analogWrite(pwmPinLinks, 100);
    startMillis = millis();
    while(millis() - startMillis < 300) {
        display.displayTime();
    }
    analogWrite(pwmPinLinks, 0);
    analogWrite(pwmPinRechts, 0);
    digitalWrite(directionPinRechts, rechts_vooruit);
    startMillis = millis();
    while(millis() - startMillis < 200) {
        display.displayTime();
    }

}

bool MotorController::checkFinish() {
    // Add your implementation here
    return false;
}

void MotorController::moveForward() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arrayahead[2]);
    analogWrite(pwmPinLinks, arrayahead[0]);
}

void MotorController::moveBackward() {
    digitalWrite(directionPinRechts, rechts_achteruit);
    digitalWrite(directionPinLinks, links_achteruit);
    analogWrite(pwmPinRechts, arrayreverse[2]);
    analogWrite(pwmPinLinks, arrayreverse[0]);
}

void MotorController::bigLeft(Display display) {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_achteruit);
    analogWrite(pwmPinRechts, arraybigleft[2]);
    analogWrite(pwmPinLinks, arraybigleft[0]);
    startMillis = millis();
    while(millis() - startMillis < 100) {
        display.displayTime();
    }
}

void MotorController::bigRight(Display display) {
    digitalWrite(directionPinRechts, rechts_achteruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraybigright[2]);
    analogWrite(pwmPinLinks, arraybigright[0]);
    startMillis = millis();
    while(millis() - startMillis < 100) {
        display.displayTime();
    }
}

void MotorController::smallRight() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraytinyright[2]);
    analogWrite(pwmPinLinks, arraytinyright[0]);
}

void MotorController::stop() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, 0);
    analogWrite(pwmPinLinks, 0);
}

void MotorController::smallLeft() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraytinyleft[2]);    //als iets niet werkt terug zetten naar 2
    analogWrite(pwmPinLinks, arraytinyleft[0]);     //"                                   " 0
}

void MotorController::turnAround(Display display) {
  digitalWrite(directionPinLinks, links_achteruit);
  analogWrite(pwmPinLinks, 100);
  analogWrite(pwmPinRechts, 100);
  startMillis = millis();
  while(millis() - startMillis < 450) {
      display.displayTime();
  }
  analogWrite(pwmPinRechts, 0);
  analogWrite(pwmPinLinks, 0);
  digitalWrite(directionPinLinks, links_vooruit);
//   delay(1000);
}