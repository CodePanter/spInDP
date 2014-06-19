/* 
 * File:   main.cpp
 * Author: Sietse
 *
 * Created on 10 June 2014, 10:56
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include "Vector3f.h"
#include "Matrix3f.h"
#include "WalkingAnimator.h"
#include "Leg.h"

using namespace std;

int main(int argc, char** argv) {

    /*char screen_leg [100][100];

    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
           screen_leg[x][y] = (x==50||y==50)?',':'.';
        }
    }
 
    Vector3f screenCenter(50.0, 50.0, 0.0);*/
    
  
    Vector3f input_loc = Vector3f(5.0, 0.0, 0.0);
    Vector3f input_rot = Vector3f(0.0, 0.0, 0.0);
    
    Servo servo[18];
    for(int i = 0; i < 18; i++){
        servo[i] = Servo();
    }

/*

    Vector3f spin_loc = Vector3f(0.0, 0.0, 0.0);
    Vector3f spin_rot = Vector3f(0.0, 0.0, 0.0);
    
    Vector3f next_loc = Vector3f();
    Vector3f next_rot = Vector3f();
    
    Vector3f legs_rv[6] = { // Relative turn position, relative to centre.
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
    */
    
    Leg legs[6] = {
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, false, false, false,&servo[0], &servo[1], &servo[2]),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, true, false, false,&servo[3], &servo[4], &servo[5]),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, true, false, false,&servo[6], &servo[7], &servo[8]),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, false, false, false,&servo[9], &servo[10], &servo[11]),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, true, true, false, false,&servo[12], &servo[13], &servo[14]),
        Leg(Vector3f(), 0, 0, 0,
            1.0f, false, false, false, false,&servo[15], &servo[16], &servo[17])
    };
    
    WalkingAnimator wa = WalkingAnimator(&legs[0], &legs[1], &legs[2], &legs[3], &legs[4], &legs[5]);
    
    wa.setLocRot(input_loc, input_rot);
    
    for(int i = 0; i < 6; i++){
        cout << legs[i].s1->angle << " | " << legs[i].s2->angle << " | " << legs[i].s3->angle << endl;
    }
    
/*    next_loc = spin_loc + input_loc;
    next_rot = spin_rot + input_rot;
    
    for(int i = 0; i < 6; i++){
        legs_av[i] = spin_loc + legs_rv[i].rotate(spin_rot);
        legs_dv[i] = (next_loc + legs_rv[i].rotate(next_rot)) - legs_av[i]; 
        cout << legs_dv[i] << endl;
    }
    
    for(int i = 0; i < 6; i++){
        legs[i].setPos(legs_dv[i]);
    }
    
    for(int i = 0; i < 6; i++){
        Vector3f tmp = screenCenter + (legs_dv[i]);
        screen_leg[(int)tmp.x][(int)tmp.y]  = (uint8_t)i+49;
        
        screen_leg[(int)tmp.x+1][(int)tmp.y] = '-';
        screen_leg[(int)tmp.x-1][(int)tmp.y] = '-';
        screen_leg[(int)tmp.x][(int)tmp.y+1] = '|';
        screen_leg[(int)tmp.x][(int)tmp.y-1] = '|';
    }
 
*/
    /*for(int x = 0; x < 100; x++){ // Isometric render of locations on a 100x100 grid, top-down view.
        for(int y = 0; y < 100; y++){
            cout << screen_leg[x][y] << ' ';
        }
        cout << endl;
    }*/
    return 0;
}