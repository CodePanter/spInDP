/* 
 * File:   Leg.cpp
 * Author: Sietse
 * 
 * Created on 16 June 2014, 09:57
 */

#include "Leg.h"
// X = side to side axis
// Y = forward
// Z = up

Leg::Leg() {
    this->location = Vector3f();
    this->aZeroPos = this->getZeroPos();
    this->s1_angleOffset = 0;
    this->s2_angleOffset = 0;
    this->s3_angleOffset = 0;
    this->foot_Offset = 0;
    this->s1_inverse = false;
    this->s2_inverse = false;
    this->s3_inverse = false;
    this->x_inverse = false;
}

// Full constructor.

Leg::Leg(Vector3f pos, int s1_angleOffset, int s2_angleOffset, int s3_angleOffset,
        float foot_Offset, bool s1_inverse, bool s2_inverse, bool s3_inverse, bool x_inverse, Servo* s1, Servo* s2, Servo* s3) {
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    this->s1_angleOffset = s1_angleOffset;
    this->s2_angleOffset = s2_angleOffset;
    this->s3_angleOffset = s3_angleOffset;
    this->foot_Offset = foot_Offset;
    this->s1_inverse = s1_inverse;
    this->s2_inverse = s2_inverse;
    this->s3_inverse = s3_inverse;
    this->x_inverse = x_inverse;
    this->location = Vector3f(pos.x * ((this->x_inverse) ? (-1) : (1)), pos.y, pos.z);
    this->aZeroPos = this->getZeroPos();
    this->setPos(location);
}

Leg::~Leg() {
}

int Leg::setPos(Vector3f pos) {
    this->location = Vector3f(pos.x * ((this->x_inverse) ? (-1) : (1)), pos.y, pos.z);
    cout << pos << endl;
    float x = this->location.x + this->aZeroPos.x;
    float y = this->location.y + this->aZeroPos.y;
    float z = this->location.z + this->aZeroPos.z;
    cout << Vector3f(x, y, z) << endl;

    alpha = 0.0f;
    beta = 0.0f;
    gamma = 0.0f;

    rotatedX = 0.0f;
    rotatedXtwo = 0.0f;
    alphaOne = 0.0f;
    alphaTwo = 0.0f;
    betaOne = 0.0f;
    betaTwo = 0.0f;
    diagonal = 0.0f;
    diagonalTwo = 0.0f;

    diagonal = sqrt(pow(x, 2.0f) + pow(y, 2.0f));
    rotatedX = sqrt(pow(diagonal, 2.0f) + pow(this->foot_Offset, 2.0f));
    alphaTwo = atan2(foot_Offset, diagonal);

    alphaOne = atan2(x, y);

    rotatedXtwo = rotatedX - L3;
    diagonalTwo = sqrt((-z *- z) + (rotatedXtwo * rotatedXtwo));
    if ((L1 + diagonalTwo) < L2) {
        return 1; // Position out of reach
    }
    betaOne = acos(((L1 * L1) + (diagonalTwo * diagonalTwo) - (L2 * L2)) / (2 * L1 * diagonalTwo));
    betaTwo = atan2(-z, rotatedXtwo);
    gamma = acos((pow(L2, 2.0f) + pow(L1, 2.0f) - pow(diagonalTwo, 2.0f)) / (2 * L2 * L1));

    alpha = alphaOne + alphaTwo;
    beta = betaOne - betaTwo;


    int ret = 0;


    //    Converst radians to degrees            Adds offset if required        Inverses angle if required
    ret += s1->setAngle(((((180 / M_PI) * alpha) - 90) + this->s1_angleOffset) * ((this->s1_inverse) ? (-1) : (1)), 0);
    ret += s2->setAngle(((((180 / M_PI) * beta)) + this->s2_angleOffset) * ((this->s2_inverse) ? (-1) : (1)), 0);
    ret += s3->setAngle(((((180 / M_PI) * gamma) - 90) + this->s3_angleOffset) * ((this->s3_inverse) ? (-1) : (1)), 0);

    if (ret > 0) {
        return 1; //A servo was out of range.
    }

    return 0;
}

int Leg::addPos(Vector3f addMe) {
    return this->setPos(this->location + addMe);
}

Vector3f Leg::getZeroPos() {
    return Vector3f((this->L3 + this->L1) * ((this->x_inverse) ? (-1) : (1)), this->foot_Offset, -this->L2);
}