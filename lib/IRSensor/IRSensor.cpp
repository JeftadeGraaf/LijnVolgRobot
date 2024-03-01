#include <Arduino.h>
#include <IRSensor.h>

IRSensor::IRSensor(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

bool IRSensor::getDistance() {
    return digitalRead(pin);
}