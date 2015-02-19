#include "create_routines.h"

void get_first_tribble_pile()
{
	create_drive_direct(0, 500);
	msleep(3000);
	while(!get_create_lbump() && !get_create_rbump()) {
		msleep(10);
	}
	create_stop();
}
