#include "../constants.h"
#include "../drive.h"
#include "../link_routines.h"

void move_until_et(float threshold)
{
        motor(MOT_LEFT, SPD);
        motor(MOT_RIGHT, SPD);
        set_analog_pullup(ET, 0);
        while(true)
        {
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
        move_until_et(100);
}
