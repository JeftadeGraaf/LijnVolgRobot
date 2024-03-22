#include <Arduino.h>
#include <USSensor.h>

USSensor::USSensor(int triggerPin, int echoPin) {
    USSensor::triggerPin = triggerPin;
    USSensor::echoPin = echoPin;
}

void USSensor::setup() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);
}

float USSensor::getDistance() {
    float distance = 0;
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    int duration = pulseIn(echoPin, HIGH);
    float newDistance = duration * 0.034 / 2;
    distance += newDistance;
    delay(5);
    return distance;
}