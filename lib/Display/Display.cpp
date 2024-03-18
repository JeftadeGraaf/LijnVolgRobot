#include <Display.h>
#include <Arduino.h>

Display::Display(int pin[7], int u1, int u2) {
    for (int i = 0; i < 7; i++) {
        Display::pin[i] = pin[i];
        pinMode(Display::pin[i], OUTPUT);
    }
    Display::u1 = u1;
    Display::u2 = u2;
}

void Display::setup() {
    for (int i = 0; i < 7; i++) {
        pinMode(Display::pin[i], OUTPUT);
    }
    pinMode(u1, OUTPUT);
    digitalWrite(u1, LOW);
    pinMode(u2, OUTPUT);
    digitalWrite(u2, LOW);
}

void Display::displayChar(char character) {
    int index = segmentDisplayChar.indexOf(character);
    for(int i = 0; i < 7; i++){
        int value = bitRead(segmentDisplay[index], i);
        digitalWrite(pin[i], value);
    
  }
}