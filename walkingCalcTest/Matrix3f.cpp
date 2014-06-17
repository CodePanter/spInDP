/* 
 * File:   Matrix3f.cpp
 * Author: Sietse
 * 
 * Created on 12 June 2014, 21:41
 */

#include <ostream>
#include <iostream>
#include "Vector3f.h"
#include "Matrix3f.h"
#include <cmath>

Matrix3f::Matrix3f(
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        double x3, double y3, double z3
/*        double x1, double x2, double x3,
        double y1, double y2, double y3,
        double z1, double z2, double z3*/) {
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->y1 = y1;
    this->y2 = y2;
    this->y3 = y3;
    this->z1 = z1;
    this->z2 = z2;
    this->z3 = z3;
}

Matrix3f::Matrix3f() {
    this->x1 = 0.0f;
    this->x2 = 0.0f;
    this->x3 = 0.0f;
    this->y1 = 0.0f;
    this->y2 = 0.0f;
    this->y3 = 0.0f;
    this->z1 = 0.0f;
    this->z2 = 0.0f;
    this->z3 = 0.0f;
}

Matrix3f::Matrix3f(const Matrix3f& orig) {
    this->x1 = orig.x1;
    this->x2 = orig.x2;
    this->x3 = orig.x3;
    this->y1 = orig.y1;
    this->y2 = orig.y2;
    this->y3 = orig.y3;
    this->z1 = orig.z1;
    this->z2 = orig.z2;
    this->z3 = orig.z3;
}

Matrix3f::~Matrix3f() {
}

const Vector3f Matrix3f::operator*(const Vector3f & rhs) const {
    return Vector3f(
            (this->x1 * rhs.x)+(this->x2 * rhs.y)+(this->x3 * rhs.z),
            (this->y1 * rhs.x)+(this->y2 * rhs.y)+(this->y3 * rhs.z),
            (this->z1 * rhs.x)+(this->z2 * rhs.y)+(this->z3 * rhs.z)
            );
}

const Matrix3f Matrix3f::operator*(const Matrix3f & rhs) const {
    return Matrix3f(
            (this->x1 * rhs.x1)+(this->x2 * rhs.y1)+(this->x3 * rhs.z1), (this->x1 * rhs.x2)+(this->x2 * rhs.y2)+(this->x3 * rhs.z2), (this->x1 * rhs.x3)+(this->x2 * rhs.y3)+(this->x3 * rhs.z3),
            (this->y1 * rhs.x1)+(this->y2 * rhs.y1)+(this->y3 * rhs.z1), (this->y1 * rhs.x2)+(this->y2 * rhs.y2)+(this->y3 * rhs.z2), (this->y1 * rhs.x3)+(this->y2 * rhs.y3)+(this->y3 * rhs.z3),
            (this->z1 * rhs.x1)+(this->z2 * rhs.y1)+(this->z3 * rhs.z1), (this->z1 * rhs.x2)+(this->z2 * rhs.y2)+(this->z3 * rhs.z2), (this->z1 * rhs.x3)+(this->z2 * rhs.y3)+(this->z3 * rhs.z3)
            );
}

const Matrix3f Matrix3f::operator+(const Matrix3f & rhs) const {
    return Matrix3f(
            this->x1 + rhs.x1, this->x2 + rhs.x2, this->x3 + rhs.x3,
            this->y1 + rhs.y1, this->y2 + rhs.y2, this->y3 + rhs.y3,
            this->z1 + rhs.z1, this->z2 + rhs.z2, this->z3 + rhs.z3
            );
}

ostream& operator<<(ostream& os, const Matrix3f & rhs) {
    os << '|' << rhs.x1 << ", " << rhs.x2 << ", " << rhs.x3 << '|' << endl
            << '|' << rhs.y1 << ", " << rhs.y2 << ", " << rhs.y3 << '|' << endl
            << '|' << rhs.z1 << ", " << rhs.z2 << ", " << rhs.z3 << '|';
    return os;
}

Matrix3f Matrix3f::rotationX(double rot) {
    return Matrix3f(
            (1.0), (0.0), (0.0),
            (0.0), (cos(rot)), (-sin(rot)),
            (0.0), (sin(rot)), (cos(rot))
            );
}

Matrix3f Matrix3f::rotationY(double rot) {
    return Matrix3f(
            (cos(rot)), (0.0), (sin(rot)),
            (0.0), (1.0), (0.0),
            (-sin(rot)), (0.0), (cos(rot))
            );
}

Matrix3f Matrix3f::rotationZ(double rot) {
    return Matrix3f(
            (cos(rot)), (-sin(rot)), (0.0),
            (sin(rot)), (cos(rot)), (0.0),
            (0.0), (0.0), (1.0)
            );
}

Matrix3f Matrix3f::unitMatrix() {
    Matrix3f m = Matrix3f(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    return m;
}