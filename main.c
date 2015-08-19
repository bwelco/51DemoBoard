#include <myhead.h>

// int T  温度
// int R 湿度  使用gettemperature();后可以打印出温湿度的值
int recv_lock = 0;
unsigned char flag1 = 0,flag2 = 0,temp1,temp2;
char strbuf[50] = {0};
int posi = 0;
int temp_lock = 0;
int card_id_posi = 0;
char cardid[50] = {0};

int temp_max = 100;
int temp_min = -40;
int light_max = 99999;
int light_min = -1;
int humi_max = 100;
int humi_min = 0;

int temp_max_flag = 0;
int temp_min_flag = 0;

int light_max_flag = 0;
int light_min_flag = 0;

int humi_max_flag = 0;
int humi_min_flag = 0;

int redlight_flag = 0;
int sound_flag = 0;

int steer_flag = 0;
int card_flag = 0;
char setcard_buf[50];
int steer_degree = 0;

int lock_2 = 0;
int lock_3 = 0;
int main()
{	
	bpm = 0;

    system_init();
	
	sendstr("Programme starting...\n");
	
	while(1)
	{   		
		while(recv_lock != 1)
		{
			if(redlight_flag == 1)
			{
				if(redlight == 1)
				    bpm = 1;
				else
					bpm = 0;
			}
			
			if(sound_key == 0 && sound_flag == 1)
			{
				//sound_delay();
				if(sound_key == 0)
				{
					out1 = 0;
					sprintf(send_message, "out1 = 0\n");
					sendstr(send_message);
					sound_key = 1;
				}
            }
			
			if(temp_min_flag == 1 && temp_min > (int)TH)
			{
				out1 = 0;
				sprintf(send_message, "out1 = 0\n");
				sendstr(send_message);
			}
			
			
			if(temp_max_flag == 1 && (int)TH > temp_max)
			{
				out1 = 1;
				sprintf(send_message, "out1 = 1\n");
				sendstr(send_message);
			}
			
			if(flag2 == 1)
			{
				sprintf(send_message, "card id = %s\n", cardid);
				sendstr(send_message);
				if(steer_flag == 1 && card_flag == 1 && 
					(strcmp(cardid, setcard_buf) == 0))
				{
					while(lock_2 == 1);
					lock_3 = 1;
					
					bpm = 1;
					stop_interrupt();
					pwm_value = turn(steer_degree);
					InitSteering();
					interrupt1_lock = 1;
					interrupt3_lock = 1;
					
					delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
					StopSteering();
					start_interrupt();
					sendstr("OK\n");
					interrupt1_lock = 0;
					interrupt3_lock = 0;
					bpm = 0;
					
					lock_3 = 0;
                }
				stop_interrupt();
				Delay500ms();
				Delay500ms();
				
				while(S2CON&S2RI)
				{
					S2CON&=~S2RI;
					temp2=S2BUF;
				}
				flag2 = 0;
				start_interrupt();
				
			}
        }
		handle_message();
		recv_lock = 0;
		
	}
}

void sound_delay(unsigned int z)
{																							   
    unsigned int i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
} 



/************串口1中断处理函数*********
void Uart() interrupt 4 using 1
{
    unsigned char recv_data;
	if(RI == 1)
	{
	    recv_data = SBUF;
		RI = 0;
	
		if(recv_data != '*')
		{
			strbuf[posi++] = recv_data;	
		}
		else
		{
			temp_lock = 0;
			strbuf[posi] = '\0';
		    recv_lock = 1;
			posi = 0;
			//while(temp_lock == 0);
			//handle_message();
		}
	}

}
/*********** 串口2中断处理函数 *****
void UART_2Interrupt(void) interrupt 8
{
	unsigned char recv_data;
	unsigned char a;
	
    if(S2CON&S2RI)
	{
		bmp = 1;
		recv_data = S2BUF;
		S2CON&=~S2RI;
	
		if(recv_data != 0x03)
		{
			cardid[card_id_posi++] = recv_data;	
		}
		else
		{
			cardid[card_id_posi++] = '\0';
			card_id_posi = 0;	
			flag2 = 1;
		}
	} 
}

void UART_2Interrupt(void) interrupt 8
{
	if(S2CON&S2RI)
	{
		S2CON&=~S2RI;
		temp2=S2BUF;
		if(temp2 == 0x02)
		{
			card_id_posi = 0;
			
        }
		if(temp2 != 0x02 && temp2 != 0x03)
		{
			cardid[card_id_posi++] = temp2;
		}
		if(temp2 == 0x03)
		{
			flag2 = 1;
			cardid[card_id_posi - 2] = '\0';
		}
	} 
}

*/
