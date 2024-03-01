#ifndef IRSensor_H_
#define IRSensor_H_

class IRSensor {
    private:
        int pin;
    public:
        IRSensor(int pin);
        bool getDistance();

};

#endif