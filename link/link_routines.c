#include "link_routines.h"
#include "constants.h"

void lift_arm() 
{
	ssp(ARM_SERVO, 2047);
}

void ping(int drive_port_1, int drive_port_2)
{
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	
	motor(drive_port_1, -30);
	motor(drive_port_2, -30);
	
	msleep(5000);
	thread_destroy(tid);
}
