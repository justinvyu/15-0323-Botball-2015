#include <stdio.h>
#include <math.h>

#define TEST

#include "link_routines.h"

void drive_to_pole()
{
	// Add touch sensor stuff after Charlie is done modifying it
	motor(MOT_LEFT, 40);
	motor(MOT_RIGHT, 40);
	msleep(6000);	
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
	
	w();
	e();
	left(ks/2, 90);
	backward(15);
	forward(10);
	right(ks/2, 90);
	
	drive_to_pole();
	ping();
}

#endif

#ifdef TEST

int main()
{
	initialize();
	w();
	e();
	
	backward(10);
	
	right(ks/2, 50);
	drive_to_pole();
	ping();
	return 0;
}

#endif
