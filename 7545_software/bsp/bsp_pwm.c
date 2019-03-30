#include "bsp_pwm.h"

#if 0
unsigned int xdata PWMRD_41  _at_  0x742;
unsigned int xdata PWMRD_42  _at_  0x744;
unsigned int xdata PWMRD_43  _at_  0x746;

unsigned int xdata PWMRD_Temp;



void Pwm_Init(void)
{
     	//设置了周期为200us，占空比为50%的PWM波形
	PWMCON = 0x7F;    //       //周期设置低8位,200us
       PWMCFG = 0x8C;  //         //7:开关  5-4：时钟源选择  3-0：周期设置高4位	
	PWMRD_Temp = 0x8000 | 0x640;     //PWM的占空比调节寄存只可写,所以可借用变量PWMRD_temp来读写占空比的值
	PWMRD_41 = PWMRD_Temp;
       PWMRD_42 = PWMRD_Temp;
       PWMRD_43 = PWMRD_Temp;
}
#endif




