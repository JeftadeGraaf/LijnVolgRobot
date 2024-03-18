#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>

class Display {
    private:
        int pin[7];
        int u1 = 18;
        int u2 = 19;
        const byte segmentDisplay[14] =
        {
            // Bin digits
            B01111110, B00110000, B01101101, B01111001,   // 0123
            B00110011, B01011011, B01011111, B01110000,   // 4567
            B01111111, B01111011, B01000111, B00000110,   // 89FI
            B01011011, B00001111,                         // ST
        };
        String segmentDisplayChar = "0123456789FIST";
        

    public:
        Display(int pin[7], int u1, int u2);
        void setup();
        void displayChar(char character);
};

#endif