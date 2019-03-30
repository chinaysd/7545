#include "bsp_uart1.h"
#include "string.h"


unsigned char Uart1SendFlag,Uart1ReceiveFlag;
unsigned char Uart1_Rev_Num,Uart1_Rev_Data,Uart1_Send_String[UART1_REV_BUF_SIZE];



void Uart1_Init(unsigned char Freq,unsigned int baud)
{
     	P1CON &= 0xF5;   //TX/RX设置为输入带上拉
	P1PH  |= 0x0A;
	
	OTCON |= 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = Freq*1000000/baud;   //波特率低位控制
	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
	IE1 |= 0x01;      //开启SSI中断
}

static void Send1_Byte(unsigned char TX1_DATA)
{
    SSDAT =  TX1_DATA;
    while(!Uart1SendFlag);
    Uart1SendFlag = 0;
}

static unsigned char Uart1_Send_Data(UART1_PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0 ; i < UART1_BUF_SIZE; i ++)
	{
		Send1_Byte(p->UART1_Buf[i]);
	}
	return 0;
}


unsigned char Uart1_Protocol_Send(unsigned char Uart1_Addr,unsigned char Uart1_Id,unsigned int Uart1_TX_Data)
{
	UART1_PROTOCOL_TX Uart1_buf;
	memset(&Uart1_buf,0,sizeof(Uart1_buf));
	Uart1_buf.Uart1_Data_Format.UART1_ADDR1 = Uart1_Addr;
	Uart1_buf.Uart1_Data_Format.UART1_ID1     = Uart1_Id;
	Uart1_buf.Uart1_Data_Format.UART1_DATA1 = UART1_Hight(Uart1_TX_Data);
	Uart1_buf.Uart1_Data_Format.UART1_DATA2 = UART1_Low(Uart1_TX_Data);
	Uart1_buf.Uart1_Data_Format.UART1_CHECKSUM = (unsigned char)(Uart1_buf.Uart1_Data_Format.UART1_ADDR1 + Uart1_buf.Uart1_Data_Format.UART1_ID1 + Uart1_buf.Uart1_Data_Format.UART1_DATA1 + Uart1_buf.Uart1_Data_Format.UART1_DATA2);
	Uart1_buf.Uart1_Data_Format.UART1_STOP1 = 0x0d;
	Uart1_buf.Uart1_Data_Format.UART1_STOP2 = 0x0a;
	return Uart1_Send_Data(&Uart1_buf);
}

unsigned char Uart1_IF_REV_ALL(void)
{
	if(Uart1_Rev_Num & 0x80)
	{ 
	     Uart1_Rev_Num &= 0x00;
	     return 1;
	}
	else
	{
	     return 0;
	}
}

void Uart1_Serial_Handle(void)
{
	Uart1_Rev_Data = SSDAT;
      if((Uart1_Rev_Num & 0x80) == 0x00)
      {
	  	if(Uart1_Rev_Num & 0x40)
	  	{
			if(Uart1_Rev_Data == 0x0a)
			{
				Uart1_Rev_Num |= 0x80;
			}
			else
			{
				Uart1_Rev_Num &= 0x00;
			}
		}
		else
		{
			if(Uart1_Rev_Data == 0x0d)
			{
				Uart1_Rev_Num |= 0x40;
			}
			else
			{
				Uart1_Send_String[Uart1_Rev_Num] = Uart1_Rev_Data;
				Uart1_Rev_Num ++;
				if(Uart1_Send_String[0] != 0x55)
				{
					Uart1_Rev_Num &= 0x00;
				}
				if(Uart1_Rev_Num > UART1_REV_BUF_SIZE)
				{
					Uart1_Rev_Num &= 0x00;
				}
			}
		}
	}
}








