// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"
#include "ET.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

void servo_set(int port,int end,float time)//,float increment)
{//position is from 0-2047
	float increment = .01;
	//printf("servo %d",port);
	float start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	float curr = start;
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
	servo_set(ARM_SERVO, ARM_UP, 4);
}

void lower_arm()
{
	ssp(ARM_SERVO, ARM_DOWN);
	msleep(500);
}

void drive_to_pole() {
	// Add touch sensor stuff after Charlie is done modifying it
	printf("DRIVING TO POLE\n");
	motor(MOT_LEFT, 50);
	motor(MOT_RIGHT, 52);
	msleep(1500);
	ao();
}

/**
 * 	Get a ping pong ball from any of the heights.
*/
void ping()
{
	servo_set(ARM_SERVO, floor(ARM_UP/3), 3);
	msleep(1000);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -50);
	msleep(500);
	ao();
	msleep(500);
	
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -40);
	msleep(500);
	ao();
	
	drive_to_pole();
	thread_wait(tid);
	thread_destroy(tid);
	//back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
	backward(12);
	lower_arm();
	forward(4);
}

/**
 * Tunnel to the "cave" area
*/
void tunnel()
{
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(300);
	ssp(PROP_SERVO, PROP_UP);
	msleep(300);
	forward_with_speed(MOT_LEFT, MOT_RIGHT, 500, 60);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(500);
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
}

/**
 *		When perpendicular to a black line, square up on it.
*/
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

/**
 * 	Drive along the middle black line and collect the golden poms.
*/
void drive_line()
{
	clear_motor_position_counter(MOT_LEFT);
	clear_motor_position_counter(MOT_RIGHT);
	
	while(get_motor_position_counter(MOT_LEFT)-50 < 19000 && get_motor_position_counter(MOT_RIGHT)-50 < 19000)
	{
		
		if(analog10(TOP_HAT_RIGHT) <= DARKNESS_THRESHOLD && analog10(TOP_HAT_LEFT) <= DARKNESS_THRESHOLD) 
		{
			motor(MOT_LEFT, 100);
			motor(MOT_RIGHT,100);
		}
		else {
			if(analog10(TOP_HAT_LEFT) >= DARKNESS_THRESHOLD)
			{
				printf("LEFT BLACK\n");
				motor(MOT_RIGHT, 100);
				motor(MOT_LEFT, 20);
			}
			if(analog10(TOP_HAT_RIGHT) >= DARKNESS_THRESHOLD)
			{
				printf("RIGHT BLACK\n");
				motor(MOT_LEFT, 100);
				motor(MOT_RIGHT, 20);
			}
		}
		msleep(50);
	}
}

void initialize() {
	enable_servo(ARM_SERVO);
	enable_servo(PROP_SERVO);
	ssp(ARM_SERVO, ARM_DOWN);
	ssp(PROP_SERVO, PROP_UP);
}

void square_on_wall() {
	
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	msleep(3000);
	ao();
}

int calibrate() {
	int i, sum = 0;
	for (i = 0; i < 20; i++) {
		sum += analog_et(ET_TURN);
		msleep(10);
	}
	int average = floor(sum/20);
	if (average > 415) {
		average = 400;
	}
	if (average >= 415) {
		average -= 15;
	}
	printf("%d\n", average);
	return average;
}

void collect_three_pings(int threshold) {

	forward(4);
	ping();
	ao();
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, 60);
	msleep(1300);
	square_on_wall();
	forward(20);
	ao();
		
	// #2
	move_until_et(ET);
	backward(2);
	printf("SEE POLE");
	right(110, ks/2);
	backward(12);
	forward(10);
	ping();

	backward(11);
	left(95, ks/2);
	//square_on_wall();
	forward(6);
	
	// #3
	move_until_et(ET);
	backward(2);
	printf("SEE POLE");
	right(115, ks/2);
	backward(11);
	forward(10);
	ping();
	backward(11);
	
	// Move across middle
	left(100, ks/2);
	forward(40);
	msleep(1000);
	forward(40);
	left(115, ks/2);
	square_on_wall();
	forward(15);
	right(115, ks/2);
	
	// #4
	move_until_et(ET);
	right(120, ks/2);
	backward(11);
	forward(10);
	ping();
	backward(14);
	left(100, ks/2);
	
	// #5
	forward(10);
	move_until_et(ET);
	backward(2);
	right(120, ks/2);
	backward(14);
	forward(10);
	ping();
	backward(11);
	left(100, ks/2);
	
	// #6
	forward(10);
	move_until_et(ET);
	backward(4);
	right(115, ks/2);
	backward(11);
	forward(10);
	ping();

	motor(MOT_RIGHT, -80);
	msleep(2500);
	ao();
	square_on_wall();
	forward(15);
	left(120, ks/2);
	backward(5);
}

#endif
