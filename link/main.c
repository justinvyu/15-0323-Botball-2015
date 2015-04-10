#include <stdio.h>
#include <math.h>

#include "link_routines.h"

int main() {
	initialize();
	// wait_for_light(LIGHT_SEN);
	shut_down_in(119);
	/*forward(30);
	msleep(2000);
	backward(30);
	msleep(2000);
	right(120, ks/2);
	left(120, ks/2);
	*/
	collect_pings();
}
