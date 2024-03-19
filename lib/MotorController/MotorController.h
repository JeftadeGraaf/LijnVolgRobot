#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

// Include any necessary libraries here

// Define your class and its member functions
class MotorController {
private:
    // Add your member variables here
    int arraytinyright[4] = {70, 1, 55, 1};
    int arraybigright[4] = {100, 1, 0, 1};
    int arrayahead[4] = {70, 1, 70, 1};
    int arraytinyleft[4] = {55, 1, 70, 1};
    int arraybigleft[4] = {0, 1, 100, 1};

    int directionPinRechts = 12; // right, low = vooruit
    int pwmPinRechts = 3;
    int directionPinLinks = 13; // left, high = vooruit
    int pwmPinLinks = 11;

    const int rechts_vooruit = 0;
    const int rechts_achteruit = 1;
    const int links_vooruit = 1;
    const int links_achteruit = 0;

    long int t1;
public:
    // Constructor(s)
    MotorController(int directionPinRechts, int pwmPinRechts, int directionPinLinks, int pwmPinLinks);
    int counter = 0;
    // Add your member functions here
    void setup();
    void turnAround();
    bool checkFinish();
    void moveForward();
    void moveBackward();
    void bigLeft();
    void bigRight();
    void smallLeft();
    void smallRight();
    void stop();
    void degrees90Left();
    void degrees90Right();
};

#endif // MOTORCONTROLLER_H