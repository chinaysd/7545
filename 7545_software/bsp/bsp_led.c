#include "bsp_led.h"




void Led_Init(void)
{
	P4CON |= 0X06;
	P4PH&= ~0X06;
	P4&= ~0X06;
}






