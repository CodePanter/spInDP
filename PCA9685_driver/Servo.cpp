#include "Servo.h"

//    MEASURED DATA
//const int FREQ    = 45;

//Constructor
Servo::Servo(int channel, PCA9685 driver, int min, int max) {
    this->channel = channel;
    this->driver = &driver;
    this->driver->setPWMFreq(45);
    this->min_angle = min;
    this->max_angle = max;
    params = (struct thread_params *)params;
    params->servo = &this;
    
}

//Destructor

Servo::~Servo() {
}

void* thread(void* args) {
}

int Servo::setAngle(int angle) {
    if ((angle > this->max_angle) || (angle < this->min_angle) {
        return 1; // INCORRECT PARAMETERS
    }

    float angleMod = (float) (angle + 90) / 180; // MAKE ANGLE ZERO TO ONE
    int paramA = (int) ((max_length_mod - min_length_mod) * angleMod) + min_length_mod;
    int paramB = 4096 - paramA;
    driver->setPWM(channel, 0, paramA);
    return 0; // DONE
}

struct thread_params {
    Servo* servo;
    int* servo_angle;
    int* servo_speed;
    bool* turning;
    bool* running;
};