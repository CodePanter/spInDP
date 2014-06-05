#include "ServoController.h"

ServoController::ServoController() {
    this->spiderstate = WAIT;
    
    const uint8_t ADDRESS = 0x40;
    const uint8_t BUS_NUM = 1;
    driver = PCA9685();
    driver.init(BUS_NUM, ADDRESS);
    driver.setPWMFreq(45);
    
    ctr = 0;
    
    leg = new Leg(&driver, 0);
    //use this when adding all the legs:
    /*
    for (int i = 0; i < 6; i++) {
        legs[i] = new Leg(&driver, i * SERVO_COUNT); //i * SERVO_COUNT for header offset
    } 
    */
}

ServoController::~ServoController() {
    delete leg;
    //see constructor
    /*
    for (int i = 0; i < 6; i++) {
        delete legs[i];
    }
    */
}

void ServoController::setState(int snum) {
    /*
    switch (snum) {
        case(0):
            this->resolveState(MOV_F, WAIT);
            break;
        case(2):
            this->resolveState(MOV_B, WAIT);
            break;
        case(4):
            this->resolveState(MOV_L, WAIT);
            break;
        case(6):
            this->resolveState(MOV_R, WAIT);
            break;
        default:
            this->spiderstate = WAIT;
            break;
    }
    */
    ctr = (ctr + 1) % 2;
    int angle = ctr ? 50 : -50;
    
    leg->twitch(angle, 150);
}

std::string ServoController::getInfo() {
    return "This is placeholder info.";
}

void ServoController::resolveState(state newstate, state cond) {
    if (this->spiderstate == cond) {
        this->spiderstate = newstate;
    } else {
        std::cout << "State conflict: state change ignored.\n";
    }
}