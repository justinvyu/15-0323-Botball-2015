#include <stdio.h>
#include <math.h>

#include "link_routines.h"

/*
Checklist


*/

int main() {	
	
	int ET_CALIBRATION = 0;

	while(ET_CALIBRATION == 0) {
		if (a_button()) {
			ET_CALIBRATION = calibrate();
		}
		msleep(20);
	}
	initialize();
	
	msleep(5000);
	collect_three_pings(ET_CALIBRATION);
	
	/*
	printf("5 seconds to position\n");
	msleep(5000);
	
	int back_more = 0;
	if (analog_et(ET) > ET_THRESHOLD_LEFT + 100) {
			back_more = 1;
	}
	clear_motor_position_counter(MOT_RIGHT);

	left(80, ks/2);
	left_et(ET_CALIBRATION);
	printf("%d\n", get_motor_position_counter(MOT_RIGHT));
	
	if (back_more == 1) {
		backward(5);
	}
	*/
	
	/*
	printf("Getting ping pong balls 2-3\n");
	int i; 
	for(i = 0; i < 2; i++) {
		move_until_et();
		left(75, 0);
		drive_to_pole();
		ping();
		right(90, 0);
		forward(15);
	}
	
	printf("Move across center\n");
	move_until_et();
	forward(20);
	move_until_et();
	forward(20);
	
	printf("Getting ping pong balls 4-5\n");
	for(i = 0; i < 2; i++) {
		move_until_et();
		left(75, 0);
		ping();
		drive_to_pole();
		right(75, 0);
		forward(10);
	}
	*/
	
	/*
	printf("Getting over the middle...\n");
	tunnel();
	square_on_wall();
	forward(10);
	
	printf("Steal a tribble from the other team...\n");
	right(60, 0);
	drive_to_pole();
	ping();
	
	backward(10);
	lower_arm();
	
	backward(10);
	left(40, 0);
	square_on_wall();
	forward(10);
	left(180, 0);
	square_on_wall();
	*/
}
