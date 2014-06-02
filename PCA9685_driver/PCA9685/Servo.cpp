/* All includes to be done in header file */
#include "Servo.h"

/* ----------------------------------------------------------------------------------- *\
 |	Each Servo object has a thread, which manipulates a physical servo, trough a pwm   |
 |	driver library, specifically for the "Adafruit PCA9685". Each thread is controlled |
 |	trough pointers, which are declared in their parent classes. Those values are in   |
 |	turn controlled trough the setAngle function.                                      |
\* ----------------------------------------------------------------------------------- */

//Constructor

Servo::Servo(int channel, PCA9685* driver, int min, int max) {
    // Initialization
    this->running = true;           // Set to false to stop loop.
    this->turning = false;          // Wether the servo is turning or not.
    this->servo_angle = 0;          // Angle the servo is to be set at.
    this->servo_speed = 1000;       // Time the servo has to go to angle, in MS
    this->channel = channel;        // Channel of servo to be controlled.
    this->driver = driver;          // Driver of servo to be controlled.
    this->driver->setPWMFreq(FREQ); // Init driver to default frequency.
    this->min_angle = min;          // Minimum angle of servo, in degs.
    this->max_angle = max;          // Maximum angle of servo, in degs.
    this->max_length = MAX_LENGTH;  // Maximum pulse width of pwm.
    this->min_length = MIN_LENGTH;  // Minumum pulse width of pwm.

    // Filling parameters for thread, into struct thread_parameters.
    this->thread_parameters.driver = 	   this->driver;
    this->thread_parameters.targetAngle = &this->servo_angle;
    this->thread_parameters.speed =       &this->servo_speed;
    this->thread_parameters.turning =     &this->turning;
    this->thread_parameters.running =     &this->running;
    this->thread_parameters.channel =      this->channel;

    // Filling minor parameters for thread, in another struct to avoid clutter.
    this->thread_parameters.modifiers.max_angle =      &this->max_angle;
    this->thread_parameters.modifiers.min_angle =      &this->min_angle;
    this->thread_parameters.modifiers.max_length =     &this->max_length;
    this->thread_parameters.modifiers.min_length =     &this->min_length;

    // Creating thread, thread_parameters* casted to void* as required for pthreads.
    pthread_create(&thread, NULL, &Servo::thread_method, (void*)&this->thread_parameters);
}

Servo::Servo(){
}

Servo::~Servo() {
    this->stop();
}


void Servo::stop() {
    this->running = false; // Breaks thread loop.
    pthread_join(thread, NULL); // Sleep until thread ends.
}


// Simple get-like functions
PCA9685 * Servo::getDriver() {
    return this->driver;
}

bool Servo::isRunning() {
    return this->running;
}

bool Servo::isTurning() {
    return this->turning;
}
// ---


int Servo::setAngle(int angle, int speed) {
    // Sets target angle for thread, if within set range.
    if ((angle > this->max_angle) || (angle < this->min_angle)) {
            return 1; // Parameter out of range.
        }
	this->speed = speed; // Speed is set first, to prevent thread using incorrect speed.
    this->targetAngle = angle;


    return 0; // DONE
}

/* Method that will be running in another thread. */
void* Servo::thread_method(void* args) { // static in header
    // Parameters casted from void* to struct pointer.
    ThreadParameters* args_struct = (ThreadParameters *) args;

    // Parameters read from struct to local vars and pointers.
	// Done to prevent confusing derefrences and such, making code unreadable.
    PCA9685* driver =  args_struct->driver;
    int* targetAngle = args_struct->targetAngle;
    int* speed =       args_struct->speed;
    bool* turning =    args_struct->turning;
    bool* running =    args_struct->running;
    int channel =      args_struct->channel;
    Modifiers mod =    args_struct->modifiers;
	// ^^ vars that aren't constantly manipulated organized in another struct.

	// Local variables for thread.
    float currentAngle = 1.0f;
    float angle = 0.0f;
    int currentTargetAngle = 0;
    float angleDif = 0.0f;
    int ticksLeft;
    int pwmLength = (int) ((*mod.max_length - *mod.min_length) * 0.5f) + *mod.min_length; // Set pwm length to middle.

	// Thread loop, breaks when running is set to false, from anywhere.
    while (*running) {
        if (!(*targetAngle == currentTargetAngle)) {
            // Calculate difference per ms
            angleDif = (((float) currentTargetAngle - (float) *targetAngle) / (float) *speed);
        }
        if (currentAngle != *targetAngle) {
            *turning = true; // Servo is turning.
                    currentAngle += angleDif; // Add angle for this tick to current angle.
                    angle = (float) (currentAngle + 90) / 180; // Make angle value from 0 to 1
					// Multiply difference between max pwm length and min pwm length by "angle", add minimum angle.
					// The result the correct pwm length for the angle.
                    pwmLength = (int) ((*mod.max_length - *mod.min_length) * angle) + *mod.min_length;
					// Call driver function to set pwm length
                    driver->setPWM(channel, 0, pwmLength);
        } else {
            *turning = false; // Servo is stationary
        }
        usleep(1000); // sleep for 1ms.
    }
}
