// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

void move_until_et(float threshold)
{
	motor(MOT_LEFT, 100);
	motor(MOT_RIGHT, 100);
	while(1)
	{
		//printf("ET: %d", analog_et(ET));
		if(analog_et(ET) >= threshold)
		{
			break;
		}
		msleep(50);
	}
	ao();
}

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

void lower_arm()
{
	servo_set(ARM_SERVO, 0 ,5);
}

void ping()
{
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, -20);
	motor(MOT_RIGHT, -20);
	msleep(3000);
	forward(15);
	thread_destroy(tid);
	lower_arm();
	backward(15);
}

/**
 * Tunnel to the "cave"
 * PROP_SERVO must be enabled
*/
void tunnel()
{
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2500);
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 500);
}

void square_on_line()
{
	while(analog(TOP_HAT_RIGHT) <= DARKNESS_THRESHOLD || analog(TOP_HAT_LEFT) <= DARKNESS_THRESHOLD) 
    {
            if(analog(TOP_HAT_RIGHT) >= DARKNESS_THRESHOLD)
            {
                    motor(MOT_LEFT, 300);
                    motor(MOT_RIGHT,200);
            }
            else if(analog(TOP_HAT_LEFT) >= DARKNESS_THRESHOLD)
            {
                    motor(MOT_RIGHT, 300);
                    motor(MOT_LEFT, 200);
            }
            else
            {
                    motor(MOT_RIGHT, 300);
                    motor(MOT_LEFT, 300);
            }
            msleep(100);
    }
    ao();
}


#endif
