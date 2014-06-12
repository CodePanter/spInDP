/* 
 * File:   Matrix3f.h
 * Author: Sietse
 *
 * Created on 12 June 2014, 21:41
 */

#ifndef MATRIX3F_H
#define	MATRIX3F_H

#include <ostream>
#include <iostream>
#include "Vector3f.h"


using namespace std;

class Vector3f;
class Matrix3f {
public:
    double x1;
    double x2;
    double x3;
    double y1;
    double y2;
    double y3;
    double z2;
    double z1;
    double z3;
    Matrix3f(double, double, double, double, double, double, double, double, double);
    Matrix3f();
    Matrix3f(const Matrix3f& orig);
    virtual ~Matrix3f();
    const Vector3f operator*(const Vector3f & rhs) const;
    const Matrix3f operator*(const Matrix3f & rhs) const;
    const Matrix3f operator+(const Matrix3f & rhs) const;
    friend ostream& operator<<(ostream& os, const Matrix3f & rhs);
    static Matrix3f rotationX(double);
    static Matrix3f rotationY(double);
    static Matrix3f rotationZ(double);
    static Matrix3f unitMatrix();
private:

};

#endif	/* MATRIX3F_H */

