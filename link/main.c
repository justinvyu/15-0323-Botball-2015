#include <stdio.h>
#include <math.h>

#include "link_routines.h"

void drive_to_pole() {
    // Add touch sensor stuff after Charlie is done modifying it
    motor(MOT_LEFT, 60);
    motor(MOT_RIGHT, 60);
    msleep(3000);
}

void ball_right()
{
    //turn_until_et(1, 100);
    ping();
    left(90, 0);
}

void ball_left()
{
    //turn_until_et(0,100);
    ping();
    right(90, 0);
}

void get_ping_pong_balls()
{
    int i;for(i = 0; i < 3; i++)
    {
        forward(15);
        move_until_et(400);
        ball_right();
        ball_left();
    }
}

void initialize() {
    enable_servo(ARM_SERVO);
    enable_servo(PROP_SERVO);
    ssp(ARM_SERVO, ARM_DOWN);
    ssp(PROP_SERVO, PROP_UP);
}

void test_et() {
    while(1) {
        printf("%d\n", analog_et(ET_TURN));
        msleep(500);
    }
}

void drive_line()
{
	clear_motor_position_counter(MOT_LEFT);
	clear_motor_position_counter(MOT_RIGHT);

	while(get_motor_position_counter(MOT_LEFT)-100 < 19000 && get_motor_position_counter(MOT_RIGHT)-100 < 19000)
	{
		
		if(analog10(TOP_HAT_LEFT) <= DARKNESS_THRESHOLD)
		{
			motor(MOT_LEFT, 50);
			motor(MOT_RIGHT, 100);
		}
		else if(analog10(TOP_HAT_RIGHT) <= DARKNESS_THRESHOLD)
		{
			motor(MOT_LEFT, 100);
		}
		else
		{
			motor(MOT_LEFT, 100);
			motor(MOT_RIGHT,100);
		}
		msleep(50);
	}
}

int main() {
    initialize();
    //	right(360, 0);

    /*tunnel();
      backward(8);
    // light sensor code, then go baack
    forward(10);

    right(60, 0);
    drive_to_pole();
    ping();

    backward(10);
    ssp(ARM_SERVO, ARM_DOWN);
    msleep(500);
    right(140, 0);

    backward(5);
    drive_to_pole();
    ping();
     */
	square_on_line();
	drive_line();
    test_et();
    //left_until_et(400);
    //get_ping_pong_balls();
}
