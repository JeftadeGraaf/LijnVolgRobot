#ifndef USSensor_H_
#define USSensor_H_

class USSensor {
    private:
        int triggerPin;
        int echoPin;
    public:
    USSensor(int triggerPin, int echoPin);
    void setup();
    float getDistance();
};
    
#endif