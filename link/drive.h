
#ifndef _DRIVE_H_
#define _DRIVE_H_

#define gmpc(port) get_motor_position_counter(port)


//primary driving code

#define MOT_LEFT 3//Rek'sai edition!
#define MOT_RIGHT 1

#define PI 3.14159265358979

#define SPD 100//turning
#define SPDl 95.//left forward
#define SPDr 82.//right forward
#define rdistmult 1.0
#define SPDlb 95.//left backward
#define SPDrb 82.//right backward
#define rdistmultb (SPDrb/SPDlb)
#define wheeldiameter 5.5 //Unique to each robot
#define ks 14.2 //Unique to each robot
#define CMtoBEMF (850/(PI*wheeldiameter))

void drive_off();
void clear_all_drive();
void drive(int mL,int mR);


void right(float degrees, float radius);
void left(float degrees, float radius);
void forward(float distance);
void multforward(float distance, float speedmult);
void backward(float distance);

#endif
