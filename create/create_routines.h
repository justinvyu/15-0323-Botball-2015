// Created on Tue February 17 2015

#include "constants.h"
#include "create_drive.h"
#include "generic.h"
# define shifttime 500

// Replace FILE with your file's name
#ifndef _CREATE_ROUTINES_H_
#define _CREATE_ROUTINES_H_

#define firstrightspeed 300
#define firstleftspeed 30
#define firstdist 250

/*void servo_set(int port,int end,float time)//,float increment)
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
}*/

void get_first_tribble_pile()
{   
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(1000);
	create_drive_direct_dist(firstrightspeed,firstleftspeed,firstdist);
	create_block();
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(1000);
	create_drive_direct_dist(-firstrightspeed,-firstleftspeed,-firstdist);
	// create_block();
	// ssp(GATE_SERVO, GATE_CLOSED );
	// msleep(1000);
	create_stop();
}


void get_second_tribble_pile()
{
	
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(1000);
	create_drive_direct_dist(150,150,200);
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(1000);
	create_stop();
}

void lift_arm() {
	motor(ARM_MOTOR, 100);
	while(digital(ARM_STOP_TOUCH_SENSOR) == 0) {
		msleep(50);
	}
	off(ARM_MOTOR);
}

void lower_arm(){
	motor(ARM_MOTOR, -100);
	msleep(5000);
	
	off(ARM_MOTOR);
	
}

void lift_arm_mid(){
	motor(ARM_MOTOR, 100);
	msleep(5100);
	
	off(ARM_MOTOR);
	
}

void lower_arm_mid(){
	motor(ARM_MOTOR, -100);
	msleep(3750);
	
	off(ARM_MOTOR);
	
}

void lower_arm_small(){
	motor(ARM_MOTOR, -100);
	msleep(900);
	
	off(ARM_MOTOR);
}

void lower_arm_tiny(){
	motor(ARM_MOTOR, -100);
	msleep(795);
	
	off(ARM_MOTOR);
}

void lift_arm_tiny(){
	motor(ARM_MOTOR, 100);
	msleep(400);
	
	off(ARM_MOTOR);
	
}

void close_gate()
{
	ssp(GATE_SERVO,GATE_CLOSED);
}

void sweep(){
	thread tid;
	tid = thread_create(close_gate); // put your closing things in close_gate()
	
	thread_start(tid);
	
	// driving back
	//while(!get_create_rbump()) {
	create_drive_direct(200,100);
	msleep(shifttime);
	//}
	
	thread_wait(tid);
	thread_destroy(tid);
}

void get_cube(){
	lift_arm_mid();
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(500);
	ao();
	create_drive_direct(-80,80);
	msleep(1500);
	create_stop();
	lower_arm_mid();
	ao();
//	msleep(6000);
	create_drive_direct(80,-80);
	msleep(1400);
	create_stop();
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(500);
	ao();	
}

void set_cube(){
	create_drive_direct(100,200);
	msleep(shifttime);
	create_drive_direct(-100,-200);
	msleep(shifttime);
	sweep();
}

void fancy_turn(){
	
	lift_arm();
	ao();
	create_drive_direct(80,80);
	msleep(3500);
	create_stop();
	motor(ARM_MOTOR, -90);
	msleep(1500);
	ao();
	create_drive_direct(-35,30);
	msleep(3000);
	create_drive_direct(30,80);
	msleep(2000);
	create_drive_direct(63,80);
	msleep(8000);
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);	
	
	create_drive_direct(-200,-100);
	msleep(shifttime);
	
	create_block();
}

void calibrate() {
	lift_arm();
	lower_arm();
}

void forwardUntilBump(){
	create_drive_direct(160,160);
	while(get_create_rbump==0 || get_create_lbump==0){
		msleep(50);
	}
}

#endif
