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
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    int duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    delay(10);
    return distance;
}