#include "Servo.h"

//    MEASURED DATA


//Constructor

Servo::Servo(int channel, PCA9685 driver, int min, int max) {
    this->running = true;
    this->turning = false;
    this->servo_angle = 0;
    this->servo_speed = 1000; // DURATION IN MS
    this->channel = channel;
    this->driver = &driver;
    this->driver->setPWMFreq(FREQ);
    this->min_angle = min;
    this->max_angle = max;
    this->max_length_mod = MAX_LENGTH;
    this->min_length_mod = MIN_LENGTH;

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

PCA9685 * Servo::getDriver() {
    return this->driver;
}

int Servo::isRunning() {
    return this->running;
}

int Servo::isTurning() {
    return this->turning;
}

int Servo::getMaxLength() {
    return this->max_length_mod;
}

int Servo::getMinLength() {
    return this->min_length_mod;
}

int Servo::setAngle(int angle, int speed) {

    if ((angle > this->max_angle) || (angle < this->min_angle) {
            return 1; // INCORRECT PARAMETERS
        }
    this->targetAngle = angle;
            this->speed = speed;

    return 0; // DONE
}

void* Servo::thread_method(void* args) {
    ThreadParameters* args_struct = (ThreadParameters *) args;

            Servo* servo = args_struct->servo;
            PCA9685* driver = args_struct->driver;
            int* targetAngle = args_struct->targetAngle;
            int* speed = args_struct->speed;
            bool* turning = args_struct->turning;
            bool* running = args_struct->running;

            float currentAngle = 0.0f;
            float angleMod = 0.0f;
            int currentTargetAngle = 0;
            float angleDif = 0.0f;
            int ticksLeft;
            int pwmFreq = servo.MAX_LENGTH;


    while (servo->isRunning()) {
        if (!(*targetAngle == currentTargetAngle)) {
            // Calculate difference per ms
            angleDif = (((float) currentTargetAngle - (float) *targetAngle) / speed);
        }
        if (currentAngle != targetAngle) {
            *turning = true; // Servo is turning.
                    currentAngle += angleDif; // Add angle for this tick to current angle.
                    angleMod = (float) (currentAngle + 90) / 180;
                    pwmFreq = (int) ((max_length_mod - min_length_mod) * angleMod) + min_length_mod;
                    driver->setPWM(channel, 0, paramA);
        } else {
            *turning = false; // Servo is stationary.
        }
        usleep(1000); // sleep for 1ms.
    }
}