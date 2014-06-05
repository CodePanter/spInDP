#include "Leg.h"

Leg::Leg(PCA9685* driver, int offset) {
    this->driver = driver;
    
    for (int i = 0; i < SERVO_COUNT; i++) {
        servos[i] = new Servo(i + offset, driver);
    }
}

Leg::Leg() {
    
}

Leg::~Leg() {
    for (int i = 0; i < SERVO_COUNT; i++) {
        delete servos[i];
    }
}

void Leg::twitch(int angle, int time) {
    servos[0]->setAngle(angle, time);
    servos[1]->setAngle(angle, time);
    servos[2]->setAngle(angle, time);
}
