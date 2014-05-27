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

    Servo(int channel, PCA9685 driver, int min = -90, int max = 90);
    ~Servo();
    int setAngle(int, int);
    int setPeriod(int);
    bool isRunning(void);
    bool isTurning(void);
    int getMaxLength(void);
    int getMinLength(void);

private:

    struct ThreadParameters{
        Servo* servo;
        PCA9685* driver;
        int* targetAngle;
        int* speed;
        bool* turning;
        bool* running;
    };
    extern ThreadParameters thread_parameters; // init constructor
    int targetAngle; // init constructor
    int speed; // init constructor
    int channel; // init constructor
    PCA9685 * driver; // init constructor
    void* thread_method(void* args);
    int max_angle; // init in constructor parameters
    int min_angle; // init in constructor parameters
    int max_length_mod; // init constructor
    int min_length_mod; // init constructor
    const int MAX_LENGTH = 412;
    const int MIN_LENGTH = 204;
    const int PERIOD = 19920;
    const int FREQ = 45;
    const int FULL_RESOLUTION = 4096;
    const int WIDTH_RESOLUTION = 208;
    pthread_t thread; // init & start constructor
    bool running; // init constructor
    bool turning; // init constructor
    int servo_angle; // init constructor
    int servo_speed; // init constructor

};
#endif