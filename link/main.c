#include <stdio.h>
#include <math.h>

#include "link_routines.h"

void drive_to_pole() {
	// Add touch sensor stuff after Charlie is done modifying it
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	msleep(3000);	
}

void initialize() {
	enable_servo(ARM_SERVO);
	enable_servo(PROP_SERVO);
	ssp(ARM_SERVO, ARM_DOWN);
	ssp(PROP_SERVO, PROP_UP);
}

int main() {
	
	right(360, 0);

	msleep(5000);

	printf("brrrrr, brrrrr, prrrrr\n");
	int i;for(i=0;i<3;i++){beep();}
	printf("I am Reksai, the Void Burrower\n");
	
	initialize();
//	right(360, 0);
	
	tunnel();
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
}
