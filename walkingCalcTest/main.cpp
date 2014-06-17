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
#include "Leg.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    char screen [100][100];
    char screen_leg [100][100];
    
    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            screen[x][y] = '.';
            screen_leg[x][y] = (x==50||y==50)?'+':'.';
        }
    }
    
    Vector3f screenCenter(50.0, 50.0, 0.0);
    
    Vector3f world = Vector3f(20.0, 10.0, 0.0);
    Vector3f pos = Vector3f(2.2, 5.5, 1.0);
    
    Vector3f spin_loc = Vector3f(0.0, 0.0, 0.0);
    Vector3f spin_rot = Vector3f(0.0, 0.0, 0.0);
    
    Leg legs[6] = {
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, false, false, false),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, true, false, false),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, true, false, false),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, false, false, false),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, true, false, false),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, false, false, false)
    };
    
    Vector3f legs_rv[6] = { // Rela
        Vector3f(  5.0575,  8.7598,  0.0 ),
        Vector3f( -5.0575,  8.7598,  0.0 ),
        Vector3f(  6.9850,  0.0,     0.0 ),
        Vector3f( -6.9850,  0.0,     0.0 ),
        Vector3f(  5.0575, -8.7598,  0.0 ),
        Vector3f( -5.0575, -8.7598,  0.0 )
    };
    
    Vector3f legs_av[6] = {// Absolute location vector
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f()
    };
    
    Vector3f legs_dv[6] = {// Difference vector per leg
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f(),
        Vector3f()
    };
    
    
    
    for(int i = 0; i < 6; i++){
        
        legs_av[i] = spin_loc + legs_rv[i].rotate(spin_rot);
        
        cout << fixed << " > " << legs_av[i] << endl;
        Vector3f tmp = screenCenter + legs_av[i];
        screen[(int)tmp.x][(int)tmp.y] = (uint8_t)i+49;
    }
    float rot = 0.0f;
    for(int i = 0; i < 100; i++){
        rot += ((M_PI/2)/100.0f);
        Vector3f tmp  = screenCenter + ((legs_rv[0] * Vector3f(3,3,3)) * (Matrix3f::rotationZ(rot) * Matrix3f::rotationY(0.0) * Matrix3f::rotationX(0.0)));
        Vector3f tmp2 = screenCenter + ((legs_rv[2] * Vector3f(3,3,3)) * (Matrix3f::rotationZ(rot) * Matrix3f::rotationY(0.0) * Matrix3f::rotationX(0.0)));
        screen_leg[(int)tmp.x][(int)tmp.y] = '|';
        screen_leg[(int)tmp2.x][(int)tmp2.y] = '-';
    }
    for(int i = 0; i < 6; i++){
        Vector3f tmp = screenCenter + (legs_rv[i] * Vector3f(3,3,3));
        screen_leg[(int)tmp.x][(int)tmp.y] = (uint8_t)i+49;
    }
    
    /*
    Vector3f leg0_r = Vector3f(  5.0,   5.0,   0.0 );
    Vector3f leg1_r = Vector3f( -5.0,   5.0,   0.0 );
    Vector3f leg2_r = Vector3f(  6.0,   0.0,   0.0 );
    Vector3f leg3_r = Vector3f( -6.0,   0.0,   0.0 );
    Vector3f leg4_r = Vector3f(  5.0,  -5.0,   0.0 );
    Vector3f leg5_r = Vector3f( -5.0,  -5.0,   0.0 );
    */
    
    Leg l1 = Leg(Vector3f(), 0, 0, 0,
            0.0f, true, false, false, false);

    //int ret = l1.setPos(Vector3f(17.0, 0, 8.5));
    cout << l1.getZeroPos() << endl;
    int ret = l1.setPos(Vector3f());
    cout << "Return code: " << ret << endl;
    Vector3f out;
    out = world + pos.rotateZ(rot);
    cout << l1.s1.angle << '|' << l1.s2.angle << '|' << l1.s3.angle << endl;
    
    for(int x = 0; x < 100; x++){ // Isometric render of locations on a 100x100 grid, top-down view.
        for(int y = 0; y < 100; y++){
            cout << screen[x][y] << ' ';
        }
        cout << endl;
    }
    cout << endl<<endl<<endl;
    for(int x = 0; x < 100; x++){ // Isometric render of locations on a 100x100 grid, top-down view.
        for(int y = 0; y < 100; y++){
            cout << screen_leg[x][y] << ' ';
        }
        cout << endl;
    }
    
    return 0;
}