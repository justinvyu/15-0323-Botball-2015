#include <stdio.h>
#include "../constants.h"
#include "../drive.h"
#include "link_routines.h"

int main()
{
        while(true)
        {
                if(analog(ET) <= 100)
                {
                        break;
                } else {
                        forward(5);
                }
                msleep(50);
        }
        ao();
}
