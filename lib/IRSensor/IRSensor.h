#ifndef IRSensor_H_
#define IRSensor_H_

class IRSensor {
    private:
        int pin;
    public:
        void setup(int pin);
        bool getValue();

};

#endif