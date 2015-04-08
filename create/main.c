// Created on Tue February 17 2015

#include "create_routines.h"

#pragma mark - Motors


#define cm(num) 10*num
#define inch(num) 25.4*num
#define firsttribbleradius 10
#define turntime 2.5




int main()
{
	create_connect();
	
	
	create_full();
	get_cube();
	create_drive_direct(65,160);
	msleep(5000);
	create_drive_direct(120,70);
	msleep(2300);
	create_drive_direct(180,180);
	msleep(6400);
	//end to end
	create_drive_direct(95,-95);
	msleep(4100);
	/*create_drive_direct(80,80);
	msleep(1500);
	create_drive_direct(95,-95);
	msleep(2000);*/
	create_stop();
	fancy_turn();
	
	
	
	
	
	
	
	
	
	create_disconnect();
	return 0;
}
