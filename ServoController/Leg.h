#ifndef LEG_H
#define	LEG_H

#include "Servo.h"
#include "PCA9685.h"

const int SERVO_COUNT = 3;

class Leg {
public:
    Leg(PCA9685* driver, int offset);
    Leg();
    virtual ~Leg();
    void twitch(int angle, int time); //test function
private:
    PCA9685* driver;
    Servo* servos[SERVO_COUNT];
};

#endif	/* LEG_H */