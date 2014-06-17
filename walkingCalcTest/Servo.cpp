// NO CONTENT, DO NOT USE WHEN IMPLEMENTING!
/* 
 * File:   Servo.cpp
 * Author: Sietse
 * 
 * Created on 16 June 2014, 10:05
 */

#include "Servo.h"

Servo::Servo() {
}

Servo::Servo(const Servo& orig) {
}

Servo::~Servo() {
}

int Servo::setAngle(int angle, int speed){
    this->speed = speed;
    this->angle = angle;
    return ((angle > 90 && angle < -90)?(0):(1));
}
// NO CONTENT, DO NOT USE WHEN IMPLEMENTING!