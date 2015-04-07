// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

//ET
int average_et(int et) {
	int i, sum = 0;
	for(i = 0; i < 3; i++) {
		sum += analog_et(et);
		msleep(5);
	}
	int average = floor(sum/3);
	printf("%d\n", average);
	return average;
}

void move_until_et(int et_port)
{
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	while(1)
	{
		//printf("ET: %d", analog_et(ET));
		if(average_et(et_port) >= ET_THRESHOLD_RIGHT)
		{
			break;
		}
		printf("%d\n", analog_et(et_port));
		msleep(5);
	}
	ao();
}

void right_et(int threshold);
void left_et(int threshold);

// change if too little 
void right_et(int threshold) {
	clear_motor_position_counter(MOT_LEFT);
	printf("RIGHT\n");
 	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, -60);
	while(average_et(ET_TURN) <= threshold) {
		//printf("%d\n", get_motor_position_counter(MOT_LEFT));
		if (get_motor_position_counter(MOT_LEFT) > 350) {
			left_et(threshold - 30);
			return;
		}
		msleep(5);
	}
	printf("past");
	back_with_speed(MOT_LEFT, MOT_RIGHT, 1000, 50);
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, -60);
	//msleep(30);
	ao();
	msleep(2000);
	backward(5);
	forward(5);
}

void left_et(int threshold) {
	clear_motor_position_counter(MOT_RIGHT);
	printf("LEFT\n");
	motor(MOT_RIGHT, 60);
	motor(MOT_LEFT, -60);
	while(analog_et(ET_TURN) <= threshold) {
		//printf("%d\n", get_motor_position_counter(MOT_RIGHT));

		if (get_motor_position_counter(MOT_RIGHT) > 350) {
			right_et(threshold - 30);
			return;
		}
		msleep(5);
	}
	printf("past");
	back_with_speed(MOT_LEFT, MOT_RIGHT, 1000, 50);
	motor(MOT_RIGHT, 60);
	motor(MOT_LEFT, -60);
	msleep(10);
	ao();
	msleep(2000);
	backward(5);
	forward(5);
	ao();
}

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
	servo_set(ARM_SERVO, ARM_UP, 5);
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
	back_with_speed(MOT_LEFT, MOT_RIGHT, 1500, 50);
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
	msleep(2000);
	/*
	while(digital(TOUCH_SENSOR_LEFT) == 0 || digital(TOUCH_SENSOR_RIGHT)) {
		msleep(10);
	}
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	msleep(500);
	*/
	ao();
}

void forward_until_et(int threshold) {
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	while (analog_et(ET_TURN) <= threshold) {
		msleep(10);
	}
	ao();
}

void back_until_et(int threshold) {
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, -60);
	while (analog_et(ET_TURN) <= threshold) {
		msleep(10);
	}
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
	right(115, ks/2);
	backward(11);
	forward(10);
	ping();

	backward(11);
	left(100, ks/2);
	//square_on_wall();
	forward(6);
	
	// #3
	move_until_et(ET);
	backward(2);
	printf("SEE POLE");
	right(125, ks/2);
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
	forward(20);
	right(115, ks/2);
	
	// #4
	move_until_et(ET);
	right(120, ks/2);
	backward(11);
	forward(10);
	ping();
	backward(12);
	left(100, ks/2);
	
	// #5
	forward(10);
	move_until_et(ET);
	right(120, ks/2);
	backward(11);
	forward(10);
	ping();
	backward(15);
	left(100, ks/2);
	
	// #6
	forward(10);
	move_until_et(ET);
	//right(120, ks/2);
	motor(MOT_RIGHT, -60);
	msleep(2500);
	backward(11);
	forward(10);
	ping();

	motor(MOT_RIGHT, -80);
	msleep(2000);
	ao();
	square_on_wall();
	forward(15);
	left(120, ks/2);
	backward(5);
}

#endif
