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

void Display::setCharacters(char charu1, char charu2) {
    Display::charu1 = charu1;
    Display::charu2 = charu2;
}

void Display::displayChar(char character, bool display) {
    if (display) {
        digitalWrite(u1, HIGH);
        digitalWrite(u2, LOW);
    } else {
        digitalWrite(u1, LOW);
        digitalWrite(u2, HIGH);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    int index = segmentDisplayChar.indexOf(character);
    for(int i = 0; i < 7; i++){
        int value = bitRead(segmentDisplay[index], i);
        digitalWrite(pin[i], value);
    }
}

void Display::displayCharacters() {
    //clear display
    digitalWrite(u1, LOW);
    for(int i = 0; i < 7; i++){
        digitalWrite(pin[i], LOW);
    }
    displayChar(charu1, true);
    delay(5);
    //clear display
    digitalWrite(u2, LOW);
    for(int i = 0; i < 7; i++){
        digitalWrite(pin[i], LOW);
    }
    
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
    while(millis() - startMillis < 1000) {
        setCharacters('S', 'T');
        displayCharacters();
    }
    setCharacters(' ', ' ');
    displayCharacters();
}

void Display::setStartTime() {
    startTime = millis();
}

void Display::displayFinishTime() {
    int finishTime = millis() - startTime;
    int seconds = finishTime / 1000;
    int tienden = getLastTwoDigitsChar(seconds, 2);
    int enen = getLastTwoDigitsChar(seconds, 1);

    for (int i = 3; i > 0; i--) {
        int startMillis = millis();
        while(millis() - startMillis < 1000) {
            setCharacters(tienden, enen);
            displayCharacters();
        }
        int startMillis2 = millis();
        while(millis() - startMillis2 < 1000) {
            setCharacters(' ', ' ');
            displayCharacters();
        }
    }
    int startMillis3 = millis();
    while(millis() - startMillis3 < 1000) {
        setCharacters('F', 'I');
        displayCharacters();
        delay(1000);
    }
}

char Display::getLastTwoDigitsChar(int number, int position) {
  // Convert the number to a string
  String numberString = String(number);
  
  // Get the length of the string
  int length = numberString.length();

  // Calculate the position from the end of the string
  int charPosition = length - position;

  // Check if the position is valid
  if (charPosition >= 0 && charPosition < length) {
    return numberString.charAt(charPosition);
  } else {
    return '0'; // Return '0' if position is out of range
  }

}