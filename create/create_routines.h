// Created on Tue February 17 2015

#include "constants.h"
#include "create_drive.h"
# define shifttime 500
// Replace FILE with your file's name
#ifndef _CREATE_ROUTINES_H_
#define _CREATE_ROUTINES_H_

#define firstrightspeed 300
#define firstleftspeed 30
#define firstdist 250

/*create_drive_direct(150,150);
	msleep(2500);
	create_drive_direct(70,170);
	msleep(3800);
	create_drive_direct(250,200);
	msleep(2800);
	create_drive_direct(150,150);
	msleep(3000);
	create_drive_direct(0,0);
	msleep(500);
	create_stop();    
	
	
	
	
	motor(ARM_MOTOR, 90);
	msleep(4000);
	ao();
	create_drive_direct(-250,-250);
	msleep(5300);
	create_stop();     
	//table to the table
	
	
	
	lift_arm();
	ao(); 
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(2000);
	create_drive_direct(80,80);
	msleep(5800);
	create_stop();
	
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(2000);
    //first turn
	create_drive_direct(-80,80);
	msleep(turntime*1000);
	create_drive_direct(80,80);
	msleep(900);
	create_stop();
	motor(ARM_MOTOR, -90);
	msleep(530);
	ao();
	//board end to another end
	create_drive_direct(-120,-120);
	msleep(4600);
	create_drive_direct(120,120); 
	msleep (4600);
	//put down the arm
	create_drive_direct(-80,80);
	msleep(turntime*1000);
	create_stop();
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(2000);
	motor(ARM_MOTOR, -90);
	msleep(4000);
	ao();
	create_drive_direct(-250,-250);
	msleep(4000);
	create_stop();
	
	//approach board 2nd time
	
	lift_arm();
	ao();
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(2000);
	create_drive_direct(80,80);
	msleep(5300);
	create_stop();
	
	//push everything to basket
	
	motor(ARM_MOTOR, -90);
	msleep(600);
	ao();
	create_drive_direct(-80,80);
	msleep(turntime*950);
	create_drive_direct(-80,-80);
	msleep(2000);
	
	create_drive_direct(120,120);
	msleep(6000);*/
	
	
	
	//sweep();*/



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
	motor(ARM_MOTOR, 90);
	while(digital(ARM_STOP_TOUCH_SENSOR) == 0) {
		msleep(50);
	}
	off(ARM_MOTOR);
}



void lower_arm(){
	motor(ARM_MOTOR, -90);
	msleep(6600);
	
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
	lift_arm();
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(2000);
	ao();
	create_drive_direct(0,80);
	msleep(3000);
	create_stop();
	lower_arm();
	ao();
	create_drive_direct(0,-80);
	msleep(2800);
	create_stop();
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(2000);
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

#endif

 /*get_first_tribble_pile();
	create_drive_direct_dist(200,200,1400);
	get_second_tribble_pile();
	
		create_block();
create_stop();*/

	/*
	
	create_drive_direct(200,200);
	msleep(3000);
*/

//create_backward(5, 300);
	/*create_drive_direct(-100,-100);
	msleep(1500);
	create_right(10, firsttribbleradius , 300);
    create_drive_direct(200,20);
	msleep(2500);
	create_forward(cm(90), 300);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(1000);
	
get_first_tribble_pile();*/




/* enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(1000);
	create_drive_direct(60, 300);
	//while(!get_create_lbump() && !get_create_rbump()) {
	//	msleep(100);
	//}
	msleep(timeforfirstpile);
	ssp(GATE_SERVO, GATE_CLOSED);
	msleep(2000);
	create_drive_direct(-60,-300);
	msleep(timeforfirstpile);
	create_stop();
*/
