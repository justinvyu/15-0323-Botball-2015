// Created on Tue February 17 2015

#include "create_routines.h"

#define cm(num) 10*num
#define inch(num) 25.4*num

void initialize() {
	enable_servo(GATE_SERVO);
}

int main() {
	create_connect();

	lift_arm();

	create_disconnect();
	// create_connect();
	
	// enable_servo(GATE_SERVO);
	// ssp(GATE_SERVO, GATE_OPEN);
	// get_first_tribble_pile();
		
	// create_right(10, 20, 300);
	
	// ssp(GATE_SERVO, GATE_CLOSED);
	// msleep(1000);
	
	// while(get_create_lbump() || get_create_rbump()) {
	// 	create_drive_direct(250, 0);
	// 	msleep(5);
	// }
		
	// create_forward(cm(90), 300);
	// printf("after");
	// ssp(GATE_SERVO, GATE_OPEN);
	// msleep(1000);
		
	// create_disconnect();
}
