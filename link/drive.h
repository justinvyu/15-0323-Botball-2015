#ifndef _DRIVE_H_
#define _DRIVE_H_

//CHANGE MOTORS TO THE ONES WE USE
//primary driving code
#define MOT_LEFT 3//Rek'sai edition!
#define MOT_RIGHT 1
#define PI 3.14159265358979
#define SPD 1000
#define SPDl 1000.
#define SPDr 1000. 
#define rdistmult (SPDr/SPDl)

#define ks 12.2//distance from one wheel to another in cm
#define wheeldiameter 3.4 //this is in cm

#define CMtoBEMF (921/wheeldiameter/PI) //921 is how many backemf ticks there are in a full wheel, take the number of units per rotation, divide by circumference
#define LBUMP digital(14)
#define RBUMP digital(15) //left/right back bump sensors (used for square_back())


#define drive_off() off(MOT_RIGHT) ;off(MOT_LEFT)
#define drive(mL,mR); {mav(MOT_LEFT,(mL)*10);mav(MOT_RIGHT,(mR)*10);}


void square_back()
{
	int _A = 0,_B = 0;
	float time = seconds();//used for timeout
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	while((_A == 0 || _B == 0) && (seconds()-time < 10))//while the bump sensors are false & it has been less than 10 seconds
	// move backwards, if the bot is bumped, turn the motor off, and break out of the loop
	{
		if (LBUMP){//if the left sensor is pressed
			off(MOT_LEFT);//turn towards wall
			_A = 1;
			} else {
			bk(MOT_LEFT);//otherwise, approach the wall more
			_A = 0;
		}
		
		if (RBUMP){//if the right sensor is pressed
			off(MOT_RIGHT);//turn towards wall
			_B = 1;
			} else {
			bk(MOT_RIGHT);//otherwise, approach the wall more
			_B = 0;
		}
		msleep(1);//give other processes time to do things
	}
	drive_off();//turn both motors off at end
}


void right(float degrees, float radius){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void left(float degrees, float radius){//turn left a number of degrees with a certain radius
	int turnlspeed;
	long turnl=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnr == 0l) return;
	turnlspeed = round((float)turnl/(float)turnr*SPD);
	mrp(MOT_RIGHT, SPD,turnr);
	if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnlspeed < 50){
		turnlspeed = 0;
		turnl=0l;
		off(MOT_LEFT);
		}else{
		mrp(MOT_LEFT,turnlspeed,turnl);
	}
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
}
void right_slow(float degrees, float radius, float spdmult){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD*spdmult,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed*spdmult,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void left_slow(float degrees, float radius, float spdmult){//turn left a number of degrees with a certain radius
	int turnlspeed;
	long turnl=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnr == 0l) return;
	turnlspeed = round((float)turnl/(float)turnr*SPD);
	mrp(MOT_RIGHT, SPD*spdmult,turnr);
	if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnlspeed < 50){
		turnlspeed = 0;
		turnl=0l;
		off(MOT_LEFT);
		}else{
		mrp(MOT_LEFT,turnlspeed*spdmult,turnl);
	}
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
}
void forward(float distance){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	mrp(MOT_RIGHT,SPDr,newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void backward(float distance){//go backward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;
	mrp(MOT_RIGHT,SPDr,-newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,-newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}

// to do: add two threshold values. >:( 

#define BLACK_SEN_THRESH 810
#define LEFT_BLACK (analog10(1)>BLACK_SEN_THRESH)
#define RIGHT_BLACK (analog10(0)>BLACK_SEN_THRESH)
//#define HIGH_POWER 1000
//#define LOW_POWER 500

void s_line_follow(float distance) //dist in cm
{
	int high = 1000;
	int low = 500;
	long position = get_motor_position_counter(MOT_RIGHT) + distance*CMtoBEMF;
	while(get_motor_position_counter(MOT_RIGHT)<=position)
	{
		msleep(1);
		//if both sensors do not detect black, drive forward
		//if the left sensor detects black, turn right
		//if the right sensor detects black, turn left
		if(!LEFT_BLACK && !RIGHT_BLACK)
		{
			mav(MOT_LEFT,high);
			mav(MOT_RIGHT,high);
		}
		else if(LEFT_BLACK)
		{
			mav(MOT_LEFT,low);
			mav(MOT_RIGHT,high);
		}
		else if(RIGHT_BLACK)
		{
			mav(MOT_RIGHT,low);
			mav(MOT_LEFT,high);
		}
	}
}

void f_line_follow(float distance)
{
	int spd = 800;
	long position = get_motor_position_counter(MOT_RIGHT) + distance*CMtoBEMF;
	while(get_motor_position_counter(MOT_RIGHT)<=position)
	{
		msleep(1);
		//if both sensors do not detect black, drive forward
		//if the left sensor detects black, turn right
		//if the right sensor detects black, turn left
		if(!LEFT_BLACK && !RIGHT_BLACK)
		{
			fd(MOT_LEFT);
			fd(MOT_RIGHT);
		}
		else if(LEFT_BLACK)
		{
			mav(MOT_LEFT,spd);
			fd(MOT_RIGHT);
		}
		else if(RIGHT_BLACK)
		{
			mav(MOT_RIGHT,spd);
			fd(MOT_LEFT);
		}
	}
}


/*
1,1-> 1
0,1-> 0
1,0-> 0
0,0-> 0
*/

#define TOUCH_FRONT digital(15)

void line_follow_touch()
{
	int high = 1000;
	int low = 500;
	long position = get_motor_position_counter(MOT_RIGHT) + 35*CMtoBEMF;
	while(!(TOUCH_FRONT || (get_motor_position_counter(MOT_RIGHT)>position)))
	{
		msleep(1);
		//if both sensors do not detect black, drive forward
		//if the left sensor detects black, turn right
		//if the right sensor detects black, turn left
		if(!LEFT_BLACK && !RIGHT_BLACK)
		{
			mav(MOT_LEFT,high);
			mav(MOT_RIGHT,high);
		}
		else if(LEFT_BLACK)
		{
			mav(MOT_LEFT,low);
			mav(MOT_RIGHT,high);
		}
		else if(RIGHT_BLACK)
		{
			mav(MOT_RIGHT,low);
			mav(MOT_LEFT,high);
		}
	}
}

#endif
