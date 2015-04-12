#include <stdio.h>
#include <math.h>

#include "link_routines.h"

int main() {
	initialize();
	// wait_for_light(LIGHT_SEN);
	printf("POSITION BY PLACING THE MIDDLE OF A RULER AT THE EDGE OF THE PVC, THEN GOING 9 INCHES. THEN, USE THE METAL BARRIER AND PLACE THE WHEEL GUARD PARALLEL TO THE BARRIER. THE ROBOT SHOULD BE BARELY IN BOUNDS (AND A LITTLE RIGHT OF THE FIRST POLE).\n");
	shut_down_in(119);
	collect_pings();
}
