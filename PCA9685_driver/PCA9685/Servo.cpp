/* All includes to be done in header file */
#include "Servo.h"

// Constructor
Servo::Servo(int channel, PCA9685* driver, int min, int max) {
    // Initialization
    this->servo_angle = 0; // Angle the servo is to be set at.
    this->channel = channel; // Channel of servo to be controlled.
    this->driver = driver; // Driver of servo to be controlled.
    this->driver->setPWMFreq(FREQ); // Init driver to default frequency.
    this->min_angle = min; // Minimum angle of servo, in degs.
    this->max_angle = max; // Maximum angle of servo, in degs.
    this->max_length = MAX_LENGTH; // Maximum pulse width of pwm.
    this->min_length = MIN_LENGTH; // Minumum pulse width of pwm.
}

Servo::Servo() {
}

Servo::~Servo() {
}

int Servo::setAngle(int angle) {
    return this->setAngle(angle, angle);
}

int Servo::setAngle(int angle, int speed) {
    if ((angle > this->max_angle) || (angle < this->min_angle)) {
        cout << angle << " is out of range.";
        return 1; // Parameter out of range.
    }
    angle = (currentAngle + 90.0f) / 180.0f; // Make angle value from 0 to 1
    // Multiply difference between max pwm length and min pwm length by "angle", add minimum angle.
    // The result the correct pwm length for the angle.
    pwmLength = (int) (((float) (MAX_LENGTH) - (float) (MIN_LENGTH) * angle) + (float) (MIN_LENGTH);
            // Call driver function to set pwm length.
            driver->setPWM(channel, 0, pwmLength);
    return 0; // DONE
}
