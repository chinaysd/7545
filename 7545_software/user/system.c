#include "system.h"
#include "string.h"


TIMEOUT_PARA TimeOut_Para[2];

unsigned int Temp_Data;
unsigned int UART1_Temp_Data;
extern unsigned char Rev_String[REV_BUF_SIZE];
extern unsigned char Uart1_Send_String[UART1_REV_BUF_SIZE];
extern unsigned char UartSendFlag,UartReceiveFlag;
extern unsigned char Uart1SendFlag,Uart1ReceiveFlag;

 int xdata PWMRD_41  _at_  0x742;
 int xdata PWMRD_42  _at_  0x744;
 int xdata PWMRD_43  _at_  0x746;

 int xdata PWMRD_Temp;
unsigned char PWMRD_41_Flag;
unsigned char i;


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


void System_Init(void)
{
	OPERCON = 0X01;       //CHKSUM����
	TimeOutDet_Init();
	Led_Init();
       Timer_Init();
	Uart1_Init(UART1_Freq,UART1_Baud);
       Uart0_Init(UART0_Freq,UART0_Baud);
       //Pwm_Init();
       simulate_uart_init();
	Key_Init();
}



void System_Handle(void)
{
	#if 0
	static unsigned char Temp_Cnts;
	if(TimeOutDet_Check(&TimeOut_Para[0]))
	{
		 TimeOut_Record(&TimeOut_Para[0],500);
		 ++ Temp_Cnts;
		 if(Temp_Cnts & 0X01)
		 {
			Protocol_Send(0xfa,0xfb,0x01);
		 }
		 else
		 {
		 	Uart1_Protocol_Send(0x55,0x88,0x01);
		 }
	}
	if(IF_REV_ALL())
	{
		Temp_Data = (unsigned int)Get_32Bit(Rev_String[2],Rev_String[3]);
		memset(&Rev_String,0,sizeof(Rev_String));
		switch (Temp_Data)
		{
			case 0x0001:
				            LED1_SET(1);
				            break;
		      case 0x0002:
			  	            LED1_SET(0);
			  	            break;
		      case 0x0004:
				            break;
		      case 0x0008:
			   	            break;
		      default:
			  	    break;
		}
	}
	if(Uart1_IF_REV_ALL())
	{
		UART1_Temp_Data = (unsigned int)UART1_Get_32Bit(Uart1_Send_String[2],Uart1_Send_String[3]);
		memset(&Uart1_Send_String,0,sizeof(Uart1_Send_String));
		switch(UART1_Temp_Data)
		{
			case 0x0001:
				           LED1_SET(1);
				           break;
		      case 0x0002:
			  	           LED1_SET(0);
			  	           break;
		      case 0x0004:
			  	           break;
		      case 0x0008:
			  	          break;
			default:
				          break;
		}
	}
	#endif
	 for(i = 0; i < S_MAX_UART_NUM; i ++){

       switch(simulate_get_userdata(i))
       {
	   	case 0x0001:
			LED1_SET(1);
			break;
	       case 0x0002:
		   	 LED1_SET(0);
		   	break;
	       case 0x0004:
		   	
		   	break;
	       case 0x0008:
		   	
		   	break;
	     default:
		 	break;
	 }






	 }
}

void EX1() interrupt	2
{
	#if 0
	static unsigned char Cnts;
	if(Key_Down())
	{
       	++ Cnts;
		if(Cnts & 0x01)
		{
			LED1_SET(1);
		}
		else
		{
			LED1_SET(0);
		}
	}
	#endif
}

/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart0�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	#if 1
	if(TI)
	{
		TI = 0;	
		UartSendFlag = 1;		
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;
		Rev_Data_Handle();		
	}	
	#endif
}

void Uart1_Int() interrupt 7   //Uart1�жϺ���
{
	if(SSCON0&0x02)    //���ͱ�־λ�ж�
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if((SSCON0&0x01))  //���ձ�־λ�ж�
	{
		SSCON0 &= 0xFE;
		Uart1ReceiveFlag = 1;
		Uart1_Serial_Handle();
	}	
}





