// Created on Tue February 17 2015

#include "constants.h"
#include "create_drive.h"

// Replace FILE with your file's name
#ifndef _CREATE_ROUTINES_H_
#define _CREATE_ROUTINES_H_

void get_first_tribble_pile()
{
	create_drive_direct(30, 400);
	while(!get_create_lbump() && !get_create_rbump()) {
		msleep(100);
	}
	create_stop();
}

#endif
