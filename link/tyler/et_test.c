#include <stdio.h>
#include "../constants.h"
#include "../drive.h"
#include "link_routines.h"

int main()
{
        create_connect();
        while(true)
        {
            create_drive_direct(100, 100);
            msleep(100);
            if(analog(ET) <= 100)
            {
                    break;
            }
        }
        create_stop();
        create_disconnect();
}
