#include "bsp_key.h"



void Key_Init(void)
{
     P4CON &= ~0X08;
     P4PH   |=  0X08;
     
     #if KEYF_ENABLE
     INT1F |= 0X08;
     #else
     INT1R |= 0X08;
     #endif
       //外部中断优先级设置
	IE  |= 0x05;	//0000 0x0x
	IE1 |= 0x08;	//0000 x000  INT2使能
	IP  |= 0X00;
	IP1 |= 0X00;
	EA = 1;
}

unsigned char Key_Down(void)
{
	#if 1
	if(KEYD_STATUS == KEY1_PIN)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	#else
      
	#endif
}

