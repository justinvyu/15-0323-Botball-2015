#include <stdio.h>
#include <math.h>

#define MAIN

#include "link_routines.h"

void drive_to_pole()
{
	// Add touch sensor stuff after Charlie is done modifying it
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 80);
	msleep(4000);	
}

void w()
{
	printf("Burrowed");
}

void initialize()
{
	enable_servo(ARM_SERVO);
	enable_servo(PROP_SERVO);
	ssp(ARM_SERVO, ARM_DOWN);
	ssp(PROP_SERVO, PROP_UP);
	
	set_analog_pullup(ET, 0); //disable pullup in order to get accurate ET values
	
}

#ifdef MAIN

int main(int argc, char** args) 
{
	printf("brrrrr, brrrrr, prrrrr\n");
	int i;for(i=0;i<3;i++){beep();}
	printf("I am Reksai, the Void Burrower\n");
	
	initialize();

	drive_to_pole();
	ping();
}

#endif

#ifdef TEST

int main()
{
	w();
	e();
	backward(10);
	e();
	return 0;
}

#endif
