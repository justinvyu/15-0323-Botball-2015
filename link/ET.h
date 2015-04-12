// Created on Tue April 7 2015

#ifndef _ET_H_
#define _ET_H_

//ET

/**
 *
 *
 */
int average_et(int et) {
	int i, sum = 0;
	for(i = 0; i < 5; i++) {
		sum += analog_et(et);
		msleep(5);
	}
	int average = floor(sum/5);
	//printf("%d\n", average);
	return average;
}

/**
 *
 *
 */
void move_until_et(int et_port)
{
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 80);
	while(1)
	{
		if(average_et(et_port) >= ET_THRESHOLD_RIGHT)
		{
			break;
		}
		//printf("%d\n", analog_et(et_port));
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

#endif
