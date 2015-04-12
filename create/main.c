// Created on Tue February 17 2015

#include "create_routines.h"
#define cm(num) 10*num
#define inch(num) 25.4*num
#define firsttribbleradius 10
#define turntime 2.5


int main()
{
	printf("1");
	create_connect();
	start();
	create_full();
	printf("2");
	get_cube();
	lift_arm_mid();
	create_right(21, 0, 80);
	create_block();
	create_drive_direct(-50,-50);
	msleep(2000);
	create_block();
	create_drive_direct_dist(165,75,100);
	create_block();
	create_drive_direct_dist(105,22,200);
	lower_arm_mid();
	
	create_drive_direct_dist(166,150,900);
	create_drive_direct_dist(160,165,450);
	create_block();//finished with pom poms
	
	create_backward(30, 160);
	create_right(85, 0, 80);//square up
	create_drive_direct(-50,-50);
	lift_arm();//while it's driving
	msleep(2000);
	lower_arm_small();
	create_block();
	create_right(50, 50, 300);//knock botgal
	lift_arm_tiny();
	create_block();
	create_right(21, 50, 80);
	create_block();
	create_backward(60, 80);
	create_block();
	lower_arm_tiny();
	create_forward(20, 80);
	create_left(63, 50, 80);//sweeps first part of pom poms
	create_block();
	msleep(20000);
	create_drive_direct_dist(160,130,300);
	create_drive_direct_dist(160,150,400);
	create_block();
	enable_servo(GATE_SERVO);
	ssp(GATE_SERVO, GATE_OPEN);
	msleep(500);	//done with sweep
	disable_servo(GATE_SERVO);
	create_backward(100, 30);

	lift_arm();
	create_backward(550, 180);
	create_block();
	
	create_drive_direct(-50,-50);
	msleep(2000);
	create_left(50, 50, 160);
	create_block();
	lower_arm_mid();
	
	create_forward(400, 160);
	create_block();
	create_forward(100, 60);
	lift_arm();
	
	create_block();
	now();
	
	create_disconnect();
	return 0;
}
