#include "bsp_timer.h"
#include "system.h"

void Timer_Init(void)
{
	TMCON = 0X07;    //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys
	
	//T0����
	TMOD |= 0x01;                 //0000 0001;Timer0���ù�����ʽ1
	TL0 = (65536 - 4500)%256;    //���ʱ�䣺ʱ��ΪFsys����16000*��1/Fsys��=1ms;
	TH0 = (65536 - 4500)/256;
	TR0 = 0;
	ET0 = 1;//��ʱ��0����
	TR0 = 1;//�򿪶�ʱ��0
	//T1����
	TMOD |= 0x20;            //0010 0000;Timer1���ù�����ʽ2
	TL1 = 256 - 160;   //���ʱ�䣺ʱ��ΪFsys����160*��1/Fsys��=10us;
	TH1 = 256 - 160;
	TR1 = 0;
	ET1 = 1;//��ʱ��1����
	TR1 = 1;//�򿪶�ʱ��1
	//T2����
	T2MOD = 0x00;
	T2CON = 0x00;	 //����Ϊ16λ���ؼĴ���
	RCAP2H = (65536-32000)/256;     //���ʱ�䣺ʱ��ΪFsys����32000*��1/Fsys��=2ms;
	RCAP2L = (65536-32000)%256;
	TR2 = 0;
	ET2 = 1;//��ʱ��2����
	TR2 = 1;//�򿪶�ʱ��2
}

/**************************************************
*�������ƣ�void timer0/1/2() interrupt 1/3/5
*�������ܣ���ʱ���жϲ�������
*��ڲ�����void
*���ڲ�����void
**************************************************/
void timer0() interrupt 1     //4ms
{
    TL0 = (65536 - 4500)%256;
    TH0 = (65536 - 4500)/256;     
    TimeOutDet_DecHandle();
    simulate_uart_rx_handle();
}

void timer1() interrupt 3
{
	
}

void Timer2Int(void) interrupt 5
{		
	TF2 = 0;   //�������
  
}









