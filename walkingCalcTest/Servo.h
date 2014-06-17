// NO CONTENT, DO NOT USE WHEN IMPLEMENTING!
/* 
 * File:   Servo.h
 * Author: Sietse
 *
 * Created on 16 June 2014, 10:05
 */

#ifndef SERVO_H
#define	SERVO_H

class Servo {
public:
    int setAngle(int, int);
    Servo();
    Servo(const Servo& orig);
    virtual ~Servo();
    int angle; 
private:
    int speed;
};

#endif	/* SERVO_H */
// NO CONTENT, DO NOT USE WHEN IMPLEMENTING!