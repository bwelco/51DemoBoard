#include <myhead.h>
unsigned int pwm_value=1500;

int interrupt1_lock = 0;
int interrupt3_lock = 0;

void delay_ms_steering(unsigned int x)
{
	unsigned int i;
	while(x--)for(i=0;i<125;i++);
}

unsigned int turn(int degree)
{
    unsigned int temp;
	float temp2;
	temp2 = (2000 / 180)*degree + 500;
	temp2 = (temp2 / (180 + 30)) * 180;
	temp = (unsigned int)temp2;
	return temp;
}
