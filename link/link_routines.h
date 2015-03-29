// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

void move_until_et(int et_port)
{
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	while(1)
	{
		//printf("ET: %d", analog_et(ET));
		if(analog_et(et_port) >= ET_THRESHOLD_RIGHT)
		{
			break;
		}
		msleep(50);
	}
	ao();
}

void right_et(int threshold);
void left_et(int threshold);

void right_et(int threshold) {
	clear_motor_position_counter(MOT_LEFT);

	ao();
 	motor(MOT_LEFT, 50);
	while(analog_et(ET_TURN) <= threshold) {
		msleep(20);
		if (get_motor_position_counter(MOT_LEFT) > 200) {
			msleep(2000);
			left_et(threshold - 50);
			return;
		}
	}
	msleep(20);
	ao();
}

void left_et(int threshold) {
	clear_motor_position_counter(MOT_RIGHT);
	
	ao();
	motor(MOT_RIGHT, 50);
	motor(MOT_LEFT, -50);
	while(analog_et(ET_TURN) <= threshold) {
		msleep(20);
		if (get_motor_position_counter(MOT_RIGHT) > 200) {
			msleep(2000);
			right_et(threshold - 50);
			return;
		}
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
	motor(MOT_RIGHT, 50);
	msleep(2000);
}

/**
 * 	Get a ping pong ball from any of the heights.-
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
	
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -50);
	msleep(1000);
	ao();
	
	drive_to_pole();
	thread_destroy(tid);
	backward(5);
	lower_arm();
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
	ao();
}

void forward_until_et(int threshold) {
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	while (analog_et(ET_TURN) <= threshold) {
		msleep(20);
	}
	ao();
}

void back_until_et(int threshold) {
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, -60);
	while (analog_et(ET_TURN) <= threshold) {
		msleep(20);
	}
	ao();
}

int calibrate() {
	int i, sum = 0;
	for (i = 0; i < 20; i++) {
		sum += analog_et(ET_TURN);
		msleep(10);
	}
	int average = floor(sum/10);
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
	//forward_until_et(500);
	forward_with_speed(MOT_LEFT, MOT_RIGHT, 800, 50);
	ping();
	backward(10);
	//back_until_et(threshold);
	ao();
	motor(MOT_LEFT, -60);
	msleep(2500);
	square_on_wall();
	forward(15);
	ao();
	msleep(5000);
	
	int i, back_more;
	for(i = 0; i < 2; i++) {

		back_more = 0;
		move_until_et(ET);
		forward(4);
		if (analog_et(ET) > ET_THRESHOLD_RIGHT + 200) {
			
			back_more = 1;
		}

		right(85, ks/2);
		right_et(threshold);
		forward_until_et(450);
		//back_with_speed(MOT_LEFT, MOT_RIGHT, 500, 40);
		ping();
		msleep(3000);
		
		if (back_more == 1) {
			backward(5);
		}
			
		backward(4);
		left(120, ks/2);
		forward(10);
	}
}

#endif
