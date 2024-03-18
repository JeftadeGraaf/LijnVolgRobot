#include <Arduino.h>
#include <IRArray.h>
#include <IRSensor.h>

IRArray::IRArray(int pins[5]) {
    for(int i = 0; i < 5; i++) {
        IRArray::pins[i] = pins[i];
        sensors[i].setup(pins[i]); // Fix: Create IRSensor object directly
    }
}

void IRArray::setup() {
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], INPUT);
    }
}

void IRArray::refreshValues() {
    for(int i = 0; i < 5; i++) {
        values[i] = sensors[i].getValue();
    }
}