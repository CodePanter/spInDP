#ifndef SERVOCONTROLLER_H
#define	SERVOCONTROLLER_H

#include <iostream>
#include <string>

#include "PCA9685.h"
#include "Leg.h"

class ServoController {
public:
    enum state { WAIT, MOV_F, MOV_B, MOV_L, MOV_R };
    
    state spiderstate;
    
    ServoController();
    virtual ~ServoController();
    void setState(int snum);
    std::string getInfo();
    
private:
    PCA9685 driver;
    Leg* leg; //todo: change this to array of legs
    int ctr; //hax
    
    void resolveState(state newstate, state cond);
};

#endif	/* SERVOCONTROLLER_H */