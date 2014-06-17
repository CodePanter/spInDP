/* 
 * File:   Vector3f.cpp
 * Author: Sietse
 * 
 * Created on 12 June 2014, 20:11
 */

#include <ostream>
#include <iostream>
#include "Matrix3f.h"
#include "Vector3f.h"

Vector3f::Vector3f(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f::Vector3f(Vector3f* vector) {
    this->x = vector->x;
    this->y = vector->y;
    this->z = vector->z;
}

Vector3f::Vector3f() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vector3f::Vector3f(const Vector3f& orig) {
        this->x = orig.x;
        this->y = orig.y;
        this->z = orig.z;
}

Vector3f::~Vector3f() {
}

const Vector3f Vector3f::operator+(const Vector3f & rhs) const {
    return Vector3f(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

const Vector3f Vector3f::operator-(const Vector3f & rhs) const {
    return Vector3f(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

const Vector3f Vector3f::operator*(const Vector3f & rhs) const {
    return Vector3f(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}

const Vector3f Vector3f::operator/(const Vector3f & rhs) const {
    return Vector3f(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
}

const Vector3f Vector3f::operator*(const Matrix3f & rhs) const {
    return Vector3f(
            (rhs.x1 * this->x)+(rhs.x2 * this->y)+(rhs.x3 * this->z),
            (rhs.y1 * this->x)+(rhs.y2 * this->y)+(rhs.y3 * this->z),
            (rhs.z1 * this->x)+(rhs.z2 * this->y)+(rhs.z3 * this->z)
            );
}

const Vector3f Vector3f::rotateX(double rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationX(rot);
}

const Vector3f Vector3f::rotateX(Vector3f rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationX(rot.x);
}

const Vector3f Vector3f::rotateY(double rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationY(rot);
}

const Vector3f Vector3f::rotateY(Vector3f rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationY(rot.y);
}

const Vector3f Vector3f::rotateZ(double rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationZ(rot);
}

const Vector3f Vector3f::rotateZ(Vector3f rot) const {
    Vector3f vec = Vector3f(this->x, this->y, this->z);
    return vec * Matrix3f::rotationZ(rot.z);
}

const Vector3f Vector3f::rotate(Vector3f rot) const {
    return Vector3f(
           ((*this) * ((Matrix3f::rotationZ(rot.z) * Matrix3f::rotationX(rot.x)) * Matrix3f::rotationY(rot.y)))
            );
}

ostream& operator<<(ostream& os, const Vector3f & rhs) {
    os << '[' << rhs.x << ", " << rhs.y << ", " << rhs.z << ']';
    return os;
}