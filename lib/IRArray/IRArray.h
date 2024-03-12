#ifndef IRArray_H_
#define IRArray_H_

#include <IRSensor.h>

class IRArray {
    private:
        int pins[5]; // Fix: Specify the size of the array
        IRSensor sensors[5];
    public:
        IRArray(int pins[5]);
        void setup();
        void refreshValues();
        int values[5];
};

#endif