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

private:

    struct ThreadParameters{
        Servo* servo;
        int* targetAngle;
        int* speed;
        bool* turning;
        bool* running;
    };
    extern ThreadParameters thread_parameters;
    int targetAngle;
    int speed;
    int channel;
    PCA9685 * driver;
    void* thread_method(void* args);
    int max_angle;
    int min_angle;
    int max_length_mod;
    int min_length_mod;
    const int MAX_LENGTH = 412;
    const int MIN_LENGTH = 204;
    const int PERIOD = 19920;
    const int FREQ = 45;
    const int FULL_RESOLUTION = 4096;
    const int WIDTH_RESOLUTION = MAX_LENGTH - MIN_LENGTH;
    pthread_t thread;
    bool running;
    bool turning;
    int servo_angle;
    int servo_speed;

};
#endif