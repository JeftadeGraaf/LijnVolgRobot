#include <Arduino.h>
#include <IRArray.h>
#include <IRSensor.h>

IRArray::IRArray(int *pins, int sizeOfArray) {
    _sizeOfArray = sizeOfArray;
    _pins = pins;
    for(int i = 0; i < _sizeOfArray; i++) {
        _sensors[i] = IRSensor(pins[i]);
    }
}

void IRArray::setup() {
    for(int i = 0; i < 5; i++) {
        Serial.println(_pins[i]);
        pinMode(_pins[i], INPUT);
    }
}

bool* IRArray::getDistances() {
    bool* distances = new bool[5];
    for(int i = 0; i < 5; i++) {
        distances[i] = _sensors[i].getDistance();
    }
    return distances;
}