#ifndef SERVO_H
#define SERVO_H

#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <stdlib.h>
#include "PCA9685.h"

using namespace std;

class Servo {
public:

    Servo(void);
    Servo(int channel, PCA9685* driver, int min = -90, int max = 90);
    ~Servo();
    int setAngle(int);
    int setAngle(int, int);

private:
     // init constructor
    //int targetAngle; // init constructor
    //int speed; // init constructor
    int channel; // init constructor
    PCA9685 * driver; // init constructor
    int max_angle; // init in constructor parameters
    int min_angle; // init in constructor parameters
    int max_length; // init constructor
    int min_length; // init constructor
    static const int MAX_LENGTH = 515;
    static const int MIN_LENGTH = 103;
    static const int PERIOD = 19920;
    static const int FREQ = 45;
    static const int FULL_RESOLUTION = 4096;
    static const int WIDTH_RESOLUTION = 208;
    int servo_angle; // init constructor
    int pwmLength;

};
#endif
