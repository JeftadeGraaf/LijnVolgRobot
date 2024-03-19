#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

// Include any necessary libraries here

// Define your class and its member functions
class MotorController {
private:
    float batterymultiplier = 1.0f; // Use float instead of int for decimal precision
    // Add your member variables here
    int arraytinyright[4] = {static_cast<int>(55 * batterymultiplier), 1, static_cast<int>(40 * batterymultiplier), 1};
    int arraybigright[4] = {static_cast<int>(50 * batterymultiplier), 1, static_cast<int>(0 * batterymultiplier), 1};
    int arrayahead[4] = {static_cast<int>(57 * batterymultiplier), 1, static_cast<int>(60 * batterymultiplier), 1};
    int arraytinyleft[4] = {static_cast<int>(40 * batterymultiplier), 1, static_cast<int>(55 * batterymultiplier), 1};
    int arraybigleft[4] = {static_cast<int>(0 * batterymultiplier), 1, static_cast<int>(50 * batterymultiplier), 1};
    int arrayreverse[4] = {static_cast<int>(57 * batterymultiplier), 1, static_cast<int>(60 * batterymultiplier), 1};

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

#endif;