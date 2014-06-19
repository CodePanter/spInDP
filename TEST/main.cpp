#include <iostream>
#include <unistd.h>

#include "PCA9685.h"

int main(int argc, char** argv) {
    const uint8_t DRIVER_01_ADR = 0x40;
    const uint8_t DRIVER_02_ADR = 0x41;
    
    PCA9685 driver1;
    PCA9685 driver2;
    driver1.init(1, DIVER_01_ADR);
    driver2.init(1, DIVER_02_ADR);
    driver1.setPWMFreq(45);
    driver2.setPWMFreq(45);
    driver1.setPWM(0, 309);
    driver1.setPWM(1, 309);
    driver1.setPWM(2, 309);
    driver1.setPWM(3, 309);
    driver1.setPWM(4, 309);
    driver1.setPWM(5, 309);
    driver1.setPWM(6, 309);
    driver1.setPWM(7, 309);
    driver1.setPWM(8, 309);
    driver1.setPWM(9, 309);
    driver1.setPWM(10, 309);
    driver1.setPWM(11, 309);
    driver1.setPWM(12, 309);
    driver1.setPWM(13, 309);
    driver1.setPWM(14, 309);
    driver1.setPWM(15, 309);
    driver2.setPWM(0, 309);
    driver2.setPWM(1, 309);
    driver2.setPWM(2, 309);
    driver2.setPWM(3, 309);
    driver2.setPWM(4, 309);
    driver2.setPWM(5, 309);
    driver2.setPWM(6, 309);
    driver2.setPWM(7, 309);
    driver2.setPWM(8, 309);
    driver2.setPWM(9, 309);
    driver2.setPWM(10, 309);
    driver2.setPWM(11, 309);
    driver2.setPWM(12, 309);
    driver2.setPWM(13, 309);
    driver2.setPWM(14, 309);
    driver2.setPWM(15, 309);
    
    return 0;
}