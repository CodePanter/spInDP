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

    Servo servos[3];
    servos[0] = Servo(0, &driver);
    servos[1] = Servo(3, &driver);
    servos[2] = Servo(4, &driver);

    bool b = true;

    servos[0].setAngle(0, 1000);
    servos[1].setAngle(0, 1000);
    servos[2].setAngle(0, 1000);

    string s;
    int i = 0;
    int t = 0;
    int val = 0;

    while (b) {
        cout << "Command: " << endl;
        cin >> s;
        switch (s) {
            case "set":
                cout << "Index: ";
                cin >> i;
                cout << " Angle: ";
                cin >> val;
                cout << " Time: ";
                cin >> t;
                servos[i].setAngle(val, t);
                cout << endl << "Set " << i << " to " << angle << " in " << time << "." << endl;
                break;
            case "walk":
                cout << "Not dun yet." << endl;
                break;
            case "stop":
                b = false;
                cout << "Stopping" << endl;
                break;
            default:
                cout << "Invalid." << endl;
                break;
        }

    }

    for (int i = 0; i < 3; i++) {
        ~servos[i];
    }

    return 0;
}
