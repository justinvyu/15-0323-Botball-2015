#include <stdio.h>
#include <math.h>

#include "link_routines.h"

int main() {	
	initialize();
	
	tunnel();
	square_on_wall();
	forward(10);
	
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
	
	printf("driving line");
	//drive_line();
	
}
