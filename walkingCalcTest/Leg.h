/* 
 * File:   Leg.h
 * Author: Sietse
 *
 * Created on 16 June 2014, 09:57
 */

#ifndef LEG_H
#define	LEG_H

#include "Servo.h"
#include "Vector3f.h"
#include <cmath>

class Leg {
public:
    Servo* s1;
    Servo* s2;
    Servo* s3;
    
    Vector3f getZeroPos();
    
    int s1_angleOffset;
    int s2_angleOffset;
    int s3_angleOffset;
    float foot_Offset;
    bool s1_inverse;
    bool s2_inverse;
    bool s3_inverse;

    bool x_inverse;

    Leg();
    Leg(Vector3f pos, int s1_angleOffset, int s2_angleOffset, int s3_angleOffset,
            float foot_Offset, bool s1_inverse, bool s2_inverse, bool s3_inverse, bool x_inverse, Servo* s1, Servo* s2, Servo* s3);
    virtual ~Leg();
    int setPos(Vector3f);
    int addPos(Vector3f);
private:
    Vector3f aZeroPos; // position where all sero angles are 0.
    Vector3f location;
    
    const float L1 =  6.30f;
    const float L2 = 12.84f;
    const float L3 =  2.52f;

    float alpha;
    float beta;
    float gamma;

    float rotatedX;
    float rotatedXtwo;
    float alphaOne;
    float alphaTwo;
    float betaOne;
    float betaTwo;
    float diagonal;
    float diagonalTwo;
};

#endif	/* LEG_H */

