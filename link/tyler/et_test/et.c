void move_until_et(float threshold) // threshold is 400 (usually)
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
