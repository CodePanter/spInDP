#ifndef SERVO_H
#define SERVO_H

#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "PCA9685.h"

using namespace std;

class Servo {
public:

    Servo(void);
    Servo(int channel, PCA9685* driver, int min = -90, int max = 90);
    void stop(void);
    ~Servo();
    PCA9685* getDriver(void);
    int setAngle(int, int);
    int setPeriod(int);
    bool isRunning(void);
    bool isTurning(void);

private:

    struct Modifiers {
        int* max_angle;
        int* min_angle;
        int* max_length;
        int* min_length;
    };

    struct ThreadParameters {
        PCA9685* driver;
        int* targetAngle;
        int* speed;
        bool* turning;
        bool* running;
	int channel;
        Modifiers modifiers;
    };
    ThreadParameters thread_parameters;

     // init constructor
    //int targetAngle; // init constructor
    //int speed; // init constructor
    int channel; // init constructor
    PCA9685 * driver; // init constructor
    static void* thread_method(void*);
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
    pthread_t thread; // init & start constructor
    bool running; // init constructor
    bool turning; // init constructor
    int servo_angle; // init constructor
    int servo_speed; // init constructor

};
#endif
