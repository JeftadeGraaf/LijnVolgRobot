#include <Arduino.h>
#include <IRSensor.h>

void IRSensor::setup(int pin){
    pinMode(pin, INPUT);
    IRSensor::pin = pin;
}

bool IRSensor::getValue() {
    return digitalRead(pin);
}