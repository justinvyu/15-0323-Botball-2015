#include <stdio.h>
#include <math.h>

#include "link_routines.h"

int main() {
	initialize();
	// wait_for_light(LIGHT_SEN);
	shut_down_in(119);
	collect_three_pings(410);
}
