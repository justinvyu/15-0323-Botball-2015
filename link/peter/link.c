void slowServo(int time, int position);

int main()
{

	motor(0,50);
	motor(1,-50);
	msleep(3000);
enable_servos();
		set_servo_position(2,0);
		slowServo(1000,2047);
			motor(0,-60);
			motor(1,60);
			set_servo_position(2,0);
			msleep(3000);
	        disable_servos();
    
	
	
	
	return 0;
	
	
	
	
	
	
	}
	
	void slowServo(int time, int position){
		int current=0;
		motor(0,-30);
		motor(1,30);
		while(current<position){
			current+=position/time;
			set_servo_position(2,current);
			msleep(position/time);
			printf("%d\n",current);
			
				motor(1,-30);
				motor(0,30);
			
		}
	}
	
	
	
	
	
	/*int touchsensor()
	{  
		while(1)
		{   ao();
			enable_servos();
			motor(0,-20);
			motor(1,20);
			msleep(2000);
	        set_servo_position(2,1024);
	        msleep(2000);
			motor(0,20);
			motor(0,-20);
	        set_servo_position(2,2047);
	        msleep(2000);
			motor(0,-20);
			motor(1,20);
			msleep(2000);
			set_servo_position(2,0);
			msleep(3000);
	        disable_servos();
			
			
			
			
			
			
			
			
			
			
			}
		}*/
