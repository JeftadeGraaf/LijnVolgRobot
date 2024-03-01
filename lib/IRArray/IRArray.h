#ifndef IRArray_H_
#define IRArray_H_

#include <IRSensor.h>

class IRArray {
    private:
        IRSensor* _sensors;
        int *_pins; // Fix: Specify the size of the array
        int _sizeOfArray;
    public:
        IRArray(int *pins, int sizeOfArray);
        void setup();
        bool* getDistances();
};

#endif