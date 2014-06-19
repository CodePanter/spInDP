/* 
 * File:   WalkingAnimator.cpp
 * Author: Sietse
 * 
 * Created on 18 June 2014, 15:16
 */

#include "WalkingAnimator.h"

WalkingAnimator::WalkingAnimator() {
    init();
}

int WalkingAnimator::setLocRot(Vector3f loc, Vector3f rot) {
    
    cout << loc << " ||| " << rot << endl;
    next_loc = spin_loc + loc;
    next_rot = spin_rot + rot;
    cout << next_loc << " ||| " << next_rot << endl;

    for (int i = 0; i < 6; i++) {
        legs_av[i] = spin_loc + legs_rv[i].rotate(spin_rot);
        legs_dv[i] = (next_loc + legs_rv[i].rotate(next_rot)) - legs_av[i];
//        cout << (next_loc + legs_rv[i].rotate(next_rot)) - legs_av[i] << endl;
//        cout << legs_dv[i] << endl;
    }

    for (int i = 0; i < 6; i++) {
        legs[i]->setPos(legs_dv[i]);
    }
    return 0;
}

WalkingAnimator::WalkingAnimator(Leg* leg1, Leg* leg2, Leg* leg3, Leg* leg4, Leg* leg5, Leg* leg6) {
    this->legs[0] = leg1;
    this->legs[1] = leg2;
    this->legs[2] = leg3;
    this->legs[3] = leg4;
    this->legs[4] = leg5;
    this->legs[5] = leg6;

    init();
}

WalkingAnimator::WalkingAnimator(Leg* legs_p[6]) {
    for (int i = 0; i < 6; i++) {
        this->legs[i] = legs_p[i];
    }
    
    init();
}

void WalkingAnimator::init() {
    input_loc = Vector3f();
    input_rot = Vector3f();
    spin_loc = Vector3f();
    spin_rot = Vector3f();
    next_loc = Vector3f();
    next_rot = Vector3f();

    legs_rv[0] = Vector3f(5.0575, 8.7598, 0.0);
    legs_rv[1] = Vector3f(-5.0575, 8.7598, 0.0);
    legs_rv[2] = Vector3f(6.9850, 0.0, 0.0);
    legs_rv[3] = Vector3f(-6.9850, 0.0, 0.0);
    legs_rv[4] = Vector3f(5.0575, -8.7598, 0.0);
    legs_rv[5] = Vector3f(-5.0575, -8.7598, 0.0);

    for (int i = 0; i < 6; i++) {
        legs_av[i] = Vector3f();
        legs_dv[i] = Vector3f();
    }
}

WalkingAnimator::WalkingAnimator(const WalkingAnimator& orig) {
}

WalkingAnimator::~WalkingAnimator() {
}

