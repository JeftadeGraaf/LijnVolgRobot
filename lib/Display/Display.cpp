#include <Display.h>
#include <Arduino.h>

int startTime;

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
    
<<<<<<< Updated upstream
  }
=======
    displayChar(charu2, false);
    delay(5);
}

void Display::aftellen(char tienden, char enen) {
    while (true) {
        setCharacters(tienden, enen);
        int startMillis = millis();
        while(millis() - startMillis < 1000) {
            displayCharacters();
        }
        if (enen == '0') {
            if (tienden == '0') {
                break;
            }
            enen = '9';
            tienden = tienden - 1;
        } else {
            enen = enen - 1;
        } 
    }
    int startMillis = millis();
    while(millis() - startMillis < 3000) {
        setCharacters('S', 'T');
        displayCharacters();
    }
    setCharacters(' ', ' ');
    displayCharacters();
}

void setStartTime() {
   startTime = millis();
>>>>>>> Stashed changes
}