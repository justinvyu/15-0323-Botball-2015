#include "link/constants.h"

void move_until_et(float threshold)
{
        motor(MOT_LEFT, 100);
        motor(MOT_RIGHT, 100);
        while(1)
        {
				//printf("ET: %d\n", analog_et(ET));
                if(analog_et(ET) >= threshold)
                {
                        break;
                }
                msleep(50);
        }
        ao();
}

int main()
{
        move_until_et(400);
}
