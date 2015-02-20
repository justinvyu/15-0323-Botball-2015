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

/**
 * Tunnel to the "cave"
 * PROP_SERVO must be enabled
 */
void tunnel()
{
	bk_with_time(MOT_LEFT, MOT_RIGHT, 5000);
	ssp(ARM_SERVO, 2047);
	msleep(1000);
	bk_with_time(MOT_LEFT, MOT_RIGHT, 3000);
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(1000);
	bk_with_time(MOT_LEFT, MOT_RIGHT, 3000);
	ssp(ARM_SERVO, 0);
	msleep(1000);
	ssp(PROP_SERVO, PROP_UP);
	msleep(1000);
	bk_with_time(MOT_LEFT, MOT_RIGHT, 3000);
}
