#ifndef SERVO_H
#define SERVO_H

#include "PCA9685.h"
#include <unistd.h>
#include <pthread.h>

class Servo {
public:

    Servo(int channel, PCA9685 driver, int min = -90, int max = 90);
    ~Servo();
    int setAngle(int);
    int setPeriod(int);

private:

    int channel;
    PCA9685 * driver;
    struct thread_params* params;
    int max_angle;
    int min_angle;
    int max_length_mod;
    int min_length_mod;
    const int MAX_LENGTH = 412;
    const int MIN_LENGTH = 204;
    const int PERIOD = 19920;
    
    pthread_t thread;
    
    bool running;
    bool turning;
    int servo_angle;
    int servo_speed;

};
#endif