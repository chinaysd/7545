#include "bsp_pwm.h"

#if 0
unsigned int xdata PWMRD_41  _at_  0x742;
unsigned int xdata PWMRD_42  _at_  0x744;
unsigned int xdata PWMRD_43  _at_  0x746;

unsigned int xdata PWMRD_Temp;



void Pwm_Init(void)
{
     	//����������Ϊ200us��ռ�ձ�Ϊ50%��PWM����
	PWMCON = 0x7F;    //       //�������õ�8λ,200us
       PWMCFG = 0x8C;  //         //7:����  5-4��ʱ��Դѡ��  3-0���������ø�4λ	
	PWMRD_Temp = 0x8000 | 0x640;     //PWM��ռ�ձȵ��ڼĴ�ֻ��д,���Կɽ��ñ���PWMRD_temp����дռ�ձȵ�ֵ
	PWMRD_41 = PWMRD_Temp;
       PWMRD_42 = PWMRD_Temp;
       PWMRD_43 = PWMRD_Temp;
}
#endif



