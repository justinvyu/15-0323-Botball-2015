// Created on Tue February 17 2015

#include "constants.h"
#include "drive.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)
void servo_set(int port,int end,float time)//,float increment)
{//position is from 0-2047
	float increment = .01;
	//printf("servo %d",port);
	float curr,start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	curr = start;
	if (start > end)
	{
		while(curr > end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	set_servo_position(port,end);
}

void lift_arm() 
{
	servo_set(ARM_SERVO, 2047, 5);
}

void ping()
{
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	
	// Replace with a square on the black line
	// square_on_line();
	
	motor(MOT_LEFT, -20);
	motor(MOT_RIGHT, -20);
	msleep(5000);
	
	thread_destroy(tid);
}

/**
 * Tunnel to the "cave"
 * PROP_SERVO must be enabled
 */
void e()
{
	bk_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	printf("done driving");
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(1000);
	printf("put servo down");
	bk_with_time(MOT_LEFT, MOT_RIGHT, 1000);
	ssp(PROP_SERVO, PROP_UP);
	msleep(1000);
	printf("lifted servo");
	bk_with_time(MOT_LEFT, MOT_RIGHT, 2000);
}

void square_on_line()
{
	
}


#endif