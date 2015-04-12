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
	msleep(500);
}

void lower_arm()
{
	ssp(ARM_SERVO, ARM_DOWN);
	msleep(300);
}

void drive_to_pole() {
	// Add touch sensor stuff after Charlie is done modifying it
	printf("DRIVING TO POLE\n");
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	msleep(1500);
	ao();
}

/**
 * 	Get a ping pong ball from any of the heights.
*/
void ping()
{
	backward(2);
	servo_set(ARM_SERVO, floor(ARM_UP/3), 2);
	//ssp(ARM_SERVO, floor(ARM_UP/3));
	msleep(300);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	msleep(800);
	ao();
	msleep(1500);
	//backward(9);
	
	//motor(MOT_LEFT, -50);
	//motor(MOT_RIGHT, -52);
	//msleep(900);
	//ao();
	
	//drive_to_pole();
	//forward(12);
	
	thread_wait(tid);
	thread_destroy(tid);
	//back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
	backward(15);
	lower_arm();
	forward(7);
}

void low_ping() {
	backward(3);
	servo_set(ARM_SERVO, ARM_UP, 4);
	msleep(600);
	backward(8);
	lower_arm();
	forward(4);
}

void low_ping_first() {
	backward(3);
	servo_set(ARM_SERVO, ARM_UP, 3.6);
	msleep(600);
	backward(4);
	lower_arm();
}

void medium_ping() {
	//servo_set(ARM_SERVO, floor(ARM_UP/4), 2);
	ssp(ARM_SERVO, floor(ARM_UP/3));
	msleep(300);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, -52);
	motor(MOT_RIGHT, -50);
	msleep(800);
	ao();
	motor(MOT_LEFT, 65);
	motor(MOT_RIGHT, 60);
	msleep(800);
	ao();
	msleep(500);
	thread_wait(tid);
	thread_destroy(tid);
	//back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
	backward(12);
	lower_arm();
	forward(8);
}

void high_ping() {
	backward(8);
	//servo_set(ARM_SERVO, floor(ARM_UP/3), 1);
	ssp(ARM_SERVO, floor(ARM_UP/3));
	msleep(300);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);

	motor(MOT_LEFT, 65);
	motor(MOT_RIGHT, 60);
	msleep(2000);
	ao();
	msleep(500);
	//backward(9);
	
	thread_wait(tid);
	thread_destroy(tid);
	//back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
	backward(15);
	lower_arm();
	forward(7);
}

void high_ping_last() {
	
	backward(8);
	//servo_set(ARM_SERVO, floor(ARM_UP/3), 1);
	ssp(ARM_SERVO, floor(ARM_UP/3));
	msleep(300);
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	/*
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -50);
	msleep(900);
	ao();
	*/
	motor(MOT_LEFT, 65);
	motor(MOT_RIGHT, 60);
	msleep(2000);
	ao();
	msleep(500);
	//backward(9);
	
	thread_wait(tid);
	thread_destroy(tid);
	//backward(9);
	
	thread_wait(tid);
	thread_destroy(tid);
	printf("!@#@#@!#@#!# "); now();
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
	
	motor(MOT_LEFT, -95);
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
	forward(5);
	low_ping_first();
	forward(18);
	msleep(10500);
	backward(12);
	motor(MOT_LEFT, -95);
	motor(MOT_RIGHT, 95);
	msleep(900);
	square_on_wall(2000);
	msleep(4000);
	forward(30);
	printf("1: ");now();

	// #2
	move_until_et(ET);
	backward(2);
	right(126, ks/2);
	backward(20);
	forward(15);
	medium_ping();

	backward(10);
	left(95, ks/2);
	forward(13);
	printf("2: ");now();
	
	// #3
	move_until_et(ET);
	backward(1);
	right(126, ks/2);
	backward(22);
	forward(17);
	high_ping();
	backward(14);
	printf("3: ");now();
	
	// Move across middle
	left(90, ks/2);
	forward(80);
	left(110, ks/2);
	square_on_wall(3200);
	forward(17);
	right(118, ks/2);
	backward(5);
	printf("middle: ");now();
	
	// #4
	move_until_et(ET);
	backward(2);
	right(122, ks/2);
	backward(16);
	forward(13);
	low_ping();
	backward(11);
	left(105, ks/2);
	printf("4: ");now();
	
	// #5
	forward(15);
	move_until_et(ET);
	backward(1);
	right(126, ks/2);
	backward(17);
	forward(12);
	medium_ping();
	backward(10);
	left(110, ks/2);
	printf("5: ");now();
	
	// #6
	forward(12);
	move_until_et(ET);
	backward(10);
	right(95, ks/2);
	printf("@!#!#!@#!#!@#"); now();
	backward(17);
	forward(18);
	high_ping_last();
	printf("6: ");now();
	
	backward(10);
	left(20, ks/2);
	printf("end: ");now();
}

#endif
