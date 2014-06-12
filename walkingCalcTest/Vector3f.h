/* 
 * File:   Vector3f.h
 * Author: Sietse
 *
 * Created on 12 June 2014, 20:11
 */

#ifndef VECTOR3F_H
#define	VECTOR3F_H

#include <ostream>
#include <iostream>
#include "Matrix3f.h"

using namespace std;

class Matrix3f;
class Vector3f {
public:
    double x;
    double y;
    double z;
    Vector3f(double, double, double);
    Vector3f(Vector3f*);
    Vector3f();
    Vector3f(const Vector3f& orig);
    virtual ~Vector3f();
    
    const Vector3f operator+(const Vector3f & rhs) const;
    const Vector3f operator-(const Vector3f & rhs) const;
    const Vector3f operator*(const Vector3f & rhs) const;
    const Vector3f operator/(const Vector3f & rhs) const;
    
    const Vector3f operator*(const Matrix3f & rhs) const;

    const Vector3f rotateX(double) const;
    const Vector3f rotateX(Vector3f) const;
    const Vector3f rotateY(double) const;
    const Vector3f rotateY(Vector3f) const;
    const Vector3f rotateZ(double) const;
    const Vector3f rotateZ(Vector3f) const;
    
    friend ostream& operator<<(ostream& os, const Vector3f & rhs);
    
private:

};

#endif	/* VECTOR3F_H */

