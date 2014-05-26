#include "Servo.h"

//    MEASURED DATA


//Constructor

Servo::Servo(int channel, PCA9685 driver, int min, int max) {
    this->channel = channel;
    this->driver = &driver;
    this->driver->setPWMFreq(FREQ);
    this->min_angle = min;
    this->max_angle = max;

    this->thread_parameters = {
        &this,
        &this->targetAngle,
        &this->speed,
        &this->turning,
        &this->running
    };
    pthread_create(&thread, NULL, &thread_method, (void*) & thread_parameters);
}

//Destructor

Servo::~Servo() {
    this->running = false; // Breaks thread loop.
    pthread_join(thread, NULL); // Sleep until thread ends.
}

int Servo::isRunning() {
    return this->running;
}

int Servo::isTurning() {
    return this->turning;
}

int Servo::setAngle(int angle, int speed) {
/* EDIT TO USE THREAD */
    if ((angle > this->max_angle) || (angle < this->min_angle) {
            return 1; // INCORRECT PARAMETERS
        }

    float angleMod = (float) (angle + 90) / 180; // Make angle 0.0f to 1.0f.
            int paramA = (int) ((max_length_mod - min_length_mod) * angleMod) + min_length_mod;
            driver->setPWM(channel, 0, paramA);

    return 0; // DONE
}

void* thread_method(void* args) {
    ThreadParameters* args_struct = (ThreadParameters *) args;
            Servo* servo = args_struct->servo;
            int* targetAngle = args_struct->targetAngle;
            int* speed = args_struct->speed;
            bool* turning = args_struct->turning;
            bool* running = args_struct->running;


            /* ADD STUFF? */
    while (servo->isRunning()) {
        /* ADD SERVO LOOP LOGIC */
    }
}