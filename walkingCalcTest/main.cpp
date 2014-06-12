/* 
 * File:   main.cpp
 * Author: Sietse
 *
 * Created on 10 June 2014, 10:56
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Vector3f.h"
#include "Matrix3f.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    Vector3f world = Vector3f(20.0, 10.0, 0.0);
    Vector3f pos = Vector3f(2.2, 5.5, 1.0);
    Vector3f rot = Vector3f(0.0, 0.0, M_PI / 2);

    Vector3f out;
    for (int i = 0; i < 1000000; i++) {
        //cout << fixed << world + pos.rotateZ(rot) << endl;
        out = world + pos.rotateZ(rot);
    }
    //Laptop Sietse timed at 1.000.000 in 355ms.
    //Desktop Sietse timed at 1.000.000 in 232ms.

    return 0;
}