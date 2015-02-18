#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "link_routines.h"

void drive_to_pole()
{
	// Add touch sensor stuff after Charlie is done modifying it
	
	motor(0, 80);
	motor(1, 80);
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
	set_analog_pullup(ET, 0); //disable pullup in order to get accurate ET values
	while(!side_button())
	{
		printf("%d\n", analog10(ET));
		msleep(1000);
	}
}
