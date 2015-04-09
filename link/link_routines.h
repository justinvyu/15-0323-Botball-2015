// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"
#include "ET.h"
#include "generic.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

void lift_arm() 
{
	servo_set(ARM_SERVO, ARM_UP, 3.5);
}

void lower_arm()
{
	ssp(ARM_SERVO, ARM_DOWN);
	msleep(500);
}

void drive_to_pole() {
	// Add touch sensor stuff after Charlie is done modifying it
	printf("DRIVING TO POLE\n");
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 62);
	msleep(1300);
	ao();
}

/**
 * 	Get a ping pong ball from any of the heights.
*/
void ping()
{
	//backward(2);
	servo_set(ARM_SERVO, floor(ARM_UP/3), 2);
	//ssp(ARM_SERVO, floor(ARM_UP/3));
	msleep(300);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -50);
	msleep(500);
	ao();
	msleep(100);
	
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -40);
	msleep(500);
	ao();
	
	drive_to_pole();
	thread_wait(tid);
	thread_destroy(tid);
	//back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
	backward(16);
	lower_arm();
	forward(7);
}

/**
 * Tunnel to the "cave" area
*/
void tunnel()
{
	ssp(PROP_SERVO, PROP_UP);
	msleep(300);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(300);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(300);
	ssp(PROP_SERVO, PROP_UP);
	msleep(300);
	forward_with_speed(MOT_LEFT, MOT_RIGHT, 500, 60);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(300);
	ssp(PROP_SERVO, PROP_UP);
	msleep(300);
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

void square_on_wall(int time) {
	
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	msleep(time);
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

void collect_pings() {
	start();
	forward(4);
	ping();
	backward(2);
	ao();
	motor(MOT_LEFT, -95);
	motor(MOT_RIGHT, 95);
	msleep(700);
	square_on_wall(800);
	forward(28);
		
	// #2
	move_until_et(ET);
	printf("SEE POLE");
	right(122, ks/2);
	backward(15);
	forward(12);
	ping();

	backward(12);
	left(97, ks/2);
	//square_on_wall();
	forward(15);
	
	// #3
	move_until_et(ET);
	//forward(2);
	printf("SEE POLE");
	right(125, ks/2);
	backward(17);
	forward(11);
	ping();
	backward(14);
	
	// Move across middle
	left(93, ks/2);
	forward(40);
	//right(4, 0);
	forward(36);
	left(105, ks/2);
	square_on_wall(4000);
	forward(22);
	right(122, ks/2);
	backward(3);
	
	// #4
	move_until_et(ET);
	right(120, ks/2);
	backward(15);
	forward(11);
	ping();
	backward(12);
	left(95, ks/2);
	
	// #5
	forward(14);
	move_until_et(ET);
	//backward(2);
	right(126, ks/2);
	backward(15);
	forward(13);
	ping();
	backward(16);
	left(100, ks/2);
	
	// #6
	forward(14);
	move_until_et(ET);
	backward(2);
	right(117, ks/2);
	backward(15);
	forward(12);
	ping();

	backward(10);
	motor(MOT_RIGHT, -100);
	msleep(1500);
	ao();
	square_on_wall(1000);
	forward(15);
	left(125, ks/2);
	backward(5);
	
	now();
}

#endif
