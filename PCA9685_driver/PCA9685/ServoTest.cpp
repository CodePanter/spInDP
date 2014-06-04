#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "PCA9685.h"
#include "Servo.h"

using namespace std;

int main() {
    const uint8_t ADDRESS = 0x40;
    const uint8_t BUS_NUM = 1;
    PCA9685 driver = PCA9685();
    driver.init(BUS_NUM, ADDRESS);
    driver.setPWMFreq(45);

    Servo* servos[3];
    servos[0] = new Servo(0, &driver/*, -90, 90*/);
    servos[1] = new Servo(1, &driver, -90, 90);
    servos[2] = new Servo(2, &driver, -90, 90);

    bool b = true;

    //servos[0]->setAngle(90, 1000);
    //servos[1]->setAngle(90, 1000);
    //servos[2]->setAngle(90, 1000);

    int s;
    int i = 0;
    int t = 0;
    int val = 0;

    while (b) {
        cout << "Command (1 = setangle  2 = walk): " << endl;
        cin >> s;
        switch (s) {
            case 1:
                cout << "Index: ";
                cin >> i;
                cout << " Angle: ";
                cin >> val;
                cout << " Time: ";
                cin >> t;
                servos[i]->setAngle(val, t);
                cout << endl << "Set " << i << " to " << val << " in " << t << "." << endl;
                break;
            case 2:
                cout << "Not dun yet." << endl;
                break;
            case 3:
                b = false;
                cout << "Stopping" << endl;
                break;
            default:
                cout << "Invalid." << endl;
                break;
        }

    }

    for (int i = 0; i < 3; i++) {
        delete servos[i];
    }

    return 0;
}
