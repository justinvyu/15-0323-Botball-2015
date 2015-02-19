// Created on Tue February 17 2015

#include "constants.h"
#include "create_routines.h"
#include "create_drive.h"

int main()
{
	create_connect();
	
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	get_first_tribble_pile();
	
	//create_backward(5, 300);
	create_right(40, 20, 300);
	
	ssp(GATE_SERVO, GATE_CLOSED);
	
	while(get_create_lbump() || get_create_rbump()) {
		create_drive_direct(500, 0);
		msleep(10);
	}
		
	create_disconnect();
}
