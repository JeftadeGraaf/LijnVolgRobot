#include "Arduino.h"
#include "MotorController.h"

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

void MotorController::turnAround() {

        digitalWrite(directionPinLinks, links_achteruit);
        analogWrite(pwmPinLinks, 100);
        analogWrite(pwmPinRechts, 100);
        delay(500);
        analogWrite(pwmPinRechts, 0);
        analogWrite(pwmPinLinks, 0);
        digitalWrite(directionPinLinks, links_vooruit);
        delay(1000);
        onWhite = false;
        functionCalledFirstTime = false;


}

bool MotorController::checkFinish() {
    // Add your implementation here
    return false;
}

void MotorController::moveForward() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, 100);
    analogWrite(pwmPinLinks, 100);
    functionCalledFirstTime = false;
}

void MotorController::bigLeft() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraybigleft[2]);
    analogWrite(pwmPinLinks, arraybigleft[0]);
    functionCalledFirstTime = false;
}

void MotorController::bigRight() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraybigright[2]);
    analogWrite(pwmPinLinks, arraybigright[0]);
    functionCalledFirstTime = false;
}

void MotorController::smallRight() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraytinyright[2]);
    analogWrite(pwmPinLinks, arraytinyright[0]);
    functionCalledFirstTime = false;
}

void MotorController::stop() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, 0);
    analogWrite(pwmPinLinks, 0);
    functionCalledFirstTime = false;
}

void MotorController::smallLeft() {
    digitalWrite(directionPinRechts, rechts_vooruit);
    digitalWrite(directionPinLinks, links_vooruit);
    analogWrite(pwmPinRechts, arraytinyleft[2]);
    analogWrite(pwmPinLinks, arraytinyleft[0]);
    functionCalledFirstTime = false;
}