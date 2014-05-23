#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "PCA9685.h"
#include "Servo.h"

using namespace std;

struct my_struct {
	Servo* servo;
	int* servo_angle;
	int* servo_time;
	bool* turning;
	bool* running;
};

void* servo_thread(void* args) {
	cout << " > Thread running!" << endl;
	struct my_struct* args2 = (struct my_struct *)args;
	Servo* servo = args2->servo;
	int* servo_angle = args2->servo_angle;
	int* servo_time = args2->servo_time;
	bool* running = args2->running;
	bool* turning = args2->turning;
	int angleDif = 0;

	int current_angle = 0;

	while(*running){
		if(*servo_angle != current_angle){
			angleDif = abs(*servo_angle - current_angle);
			if(*servo_angle > current_angle){
				current_angle++;
			} else {
				current_angle--;
			}
			*turning = true;
			servo->setAngle(current_angle);
			cout << angleDif << endl;
			if(angleDif == 5){
				usleep(100*(*servo_time));
			}else{
			if(angleDif == 5){
				usleep(200*(*servo_time));
			}else{
			if(angleDif == 5){
				usleep(550*(*servo_time));
			}else{
			if(angleDif == 5){
				usleep(800*(*servo_time));
			}else{
			if(angleDif == 5){
				usleep(1000*(*servo_time));
			}else{
			usleep(50*(*servo_time));}}}}}
		} else {
			*turning = false;
			usleep(10*1000);
		}
	}
	cout << " > Thread stopping!" << endl;
}

int main ( )
{
	const uint8_t ADDRESS = 0x40;
	const uint8_t BUS_NUM = 1;

	PCA9685 driver = PCA9685();
	driver.init(BUS_NUM, ADDRESS);
	driver.setPWMFreq(45);
	Servo servo1 = Servo(0, driver);
	Servo servo2 = Servo(1, driver);
	Servo servo3 = Servo(2, driver);

	Servo * selected = &servo1;

	servo1.setAngle(0);
	servo2.setAngle(0);
	servo3.setAngle(0);
	cout << "Angle set to 0." << endl;
	
	// Threads
	pthread_t thread_1;
	pthread_t thread_2;
	pthread_t thread_3;

	struct my_struct stp1;
	struct my_struct stp2;
	struct my_struct stp3;

	

	bool running = true;

	int servo_one_angle = 0;
	int servo_one_time = 100;
	bool servo_one_turning = false;

	int servo_two_angle = 0;
	int servo_two_time = 100;
	bool servo_two_turning = false;

	int servo_three_angle = 0;
	int servo_three_time = 100;
	bool servo_three_turning = false;

	cout << "Declared vars." << endl;

	stp1.servo = &servo1;
	stp1.servo_angle = &servo_one_angle;
	stp1.servo_time = &servo_one_time;
	stp1.running = &running;
	stp1.turning = &servo_one_turning;

	stp2.servo = &servo2;
	stp2.servo_angle = &servo_two_angle;
	stp2.servo_time = &servo_two_time;
	stp2.running = &running;
	stp2.turning = &servo_two_turning;

	stp3.servo = &servo3;
	stp3.servo_angle = &servo_three_angle;
	stp3.servo_time = &servo_three_time;
	stp3.running = &running;
	stp3.turning = &servo_three_turning;

	cout << "Assigned pointers." << endl;


	pthread_create(&thread_1, NULL, &servo_thread, (void*)&stp1);
	cout << "Created thread 1" << endl;


	pthread_create(&thread_2, NULL, &servo_thread, (void*)&stp2);
	cout << "Created thread 2" << endl;

	pthread_create(&thread_3, NULL, &servo_thread, (void*)&stp3);
	cout << "Created thread 3" << endl;

	bool b = true;
	int angle = 0;
	usleep(2000);
	cout << "!--------------!" << endl;

	while(b){
		cout << " - " << servo_one_angle << " " << servo_two_angle << " " << servo_three_angle << " - " << endl;
		cout << "Input angle in deg (-90 to 90) (111=exit|222=cycleS1|333=period|444=cycleS2|555=select)" << endl;
		cin >> angle;
		if(angle == 111){
			b = false;
		}
		if(angle == 222){
			servo_one_time = 100;
			servo_one_angle = -90;
			servo_two_time = 200;
			servo_two_angle = 90;
			servo_three_time = 400;
			servo_three_angle = -90;
			usleep(50*1000);
			while(servo_one_turning){
				usleep(10*1000);
			}
			while(servo_two_turning){
				usleep(10*1000);
			}
			while(servo_three_turning){
				usleep(10*1000);
			}
			usleep(2000*1000);
			servo_one_time = 400;
			servo_one_angle = 45;
			servo_two_time = 200;
			servo_two_angle = -60;
			servo_three_time = 100;
			servo_three_angle = 30;
			usleep(50*1000);
			while(servo_one_turning){
				usleep(10*1000);
			}
			while(servo_two_turning){
				usleep(10*1000);
			}
			while(servo_three_turning){
				usleep(10*1000);
			}

		}
		if(angle == 333){
			servo_one_angle = 0;
			servo_two_angle = 0;
			servo_three_angle = 0;
		}
		if(angle == 444){
			servo_one_angle = 0;
			servo_two_angle = 0;
			servo_three_angle = 0;
			
			cin >> angle;
			servo_one_angle = 20;

			cin >> angle;
			servo_two_angle = 20;

			cin >> angle;
			servo_three_angle = 20;

			cin >> angle;
			servo_one_angle = -20;

			cin >> angle;
			servo_two_angle = -20;

			cin >> angle;
			servo_three_angle = -20;
			angle = 444;
		}
		if(angle == 555){
			servo_one_angle = 0;
			servo_two_angle = 0;
			servo_three_angle = 0;

			usleep(50*1000);
			while(servo_one_turning){
				usleep(10*1000);
			}
			while(servo_two_turning){
				usleep(10*1000);
			}
			while(servo_three_turning){
				usleep(10*1000);
			}

			for(int i = 0; i < 10; i++){
			servo_one_time = 100;
			servo_one_angle = 45;
			servo_two_time = 100;
			servo_two_angle = -60;
			servo_three_time = 100;
			servo_three_angle = 30;


			usleep(50*1000);
			while(servo_one_turning){
				usleep(10*1000);
			}
			while(servo_two_turning){
				usleep(10*1000);
			}
			while(servo_three_turning){
				usleep(10*1000);
			}

			servo_three_time = 10;
			servo_three_angle = -60;

			usleep(50*1000);
			while(servo_three_turning){
				usleep(10*1000);
			}

			servo_one_angle = 0;
			servo_two_angle = -20;
			servo_three_angle = 0;

			usleep(50*1000);
			while(servo_one_turning){
				usleep(10*1000);
			}
			while(servo_two_turning){
				usleep(10*1000);
			}
			while(servo_three_turning){
				usleep(10*1000);
			}
			}
		}
		if((angle >= -90) && (angle <= 90)){
			cout << "DISABLED" << endl;
		}
		angle = 0;
	}
	cout << "!--------------!" << endl;

	// EXIT CODE
	cout << "Destructing..." << endl;
	driver.reset();
	running = false;
	cout << "Stopping threads..." << endl;
	pthread_join(thread_1, NULL);
	cout << "Joined thread 1" << endl;

	pthread_join(thread_2, NULL);
	cout << "Joined thread 2" << endl;

	pthread_join(thread_3, NULL);
	cout << "Joined thread 3" << endl;
	cout << "Done" << endl;
	return 0 ;
}
