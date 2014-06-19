/* 
 * File:   WalkingAnimator.h
 * Author: Sietse
 *
 * Created on 18 June 2014, 15:16
 */

#ifndef WALKINGANIMATOR_H
#define	WALKINGANIMATOR_H

#include "Leg.h"
#include "Vector3f.h"
#include "Matrix3f.h"

class WalkingAnimator {
public:
    int setLocRot(Vector3f,Vector3f);
    Leg* legs[6];
    WalkingAnimator(Leg*, Leg*, Leg*, Leg*, Leg*, Leg*);
    WalkingAnimator(Leg*[6]);
    WalkingAnimator();
    WalkingAnimator(const WalkingAnimator& orig);
    virtual ~WalkingAnimator();
private:
    void init(void);
    Vector3f input_loc;
    Vector3f input_rot;
    Vector3f spin_loc;
    Vector3f spin_rot;
    Vector3f next_loc;
    Vector3f next_rot;
    Vector3f legs_rv[6];
    Vector3f legs_av[6];
    Vector3f legs_dv[6];
};

#endif	/* WALKINGANIMATOR_H */

