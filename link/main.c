#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "drive.h"
#include "link_routines.h"

void drive_to_pole()
{
	// Add touch sensor stuff after Charlie is done modifying it
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 80);
	msleep(6000);	
}

int main(int argc, char** args) 
{
	/*
	enable_servo(ARM_SERVO);
	ssp(ARM_SERVO, 0);
	
	drive_to_pole();
	ping(0, 1);
	*/
	
	/*
	set_analog_pullup(ET, 0); //disable pullup in order to get accurate ET values
	while(!side_button())
	{
		printf("%d\n", analog10(ET));
		msleep(1000);
	}
	*/
	
	// Drive Test
	
	/*
	set_a_button_text("Forward");
	set_b_button_text("Backward");
	
	while(!side_button()) {
		if(a_button()) {
			printf("forward");
			fd_with_time(MOT_LEFT, MOT_RIGHT, 6000);
		}
		if(b_button()) {
			printf("backward");
			back_with_speed(MOT_LEFT, MOT_RIGHT, 6000, 500);
		}
	}
	*/
	
	enable_servo(PROP_SERVO);
	tunnel();

}
