#include "link/constants.h"

void move_until_et(float threshold)
{
        motor(MOT_LEFT, 100);
        motor(MOT_RIGHT, 100);
        set_analog_pullup(ET, 0);
        while(1)
        {
				printf("%d", analog10(ET));
                if(analog10(ET) <= threshold)
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
