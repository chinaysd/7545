#include "bsp_uart0.h"
#include "system.h"

unsigned char UartSendFlag,UartReceiveFlag;
unsigned char Rev_Num,Rev_Data,Rev_String[REV_BUF_SIZE];


void Uart0_Init(unsigned char Freq,unsigned int baud)
{
       P0CON &= 0xF3;   //TX/RX设置为输入带上拉
	P0PH  |= 0x0C;
    
	SCON  |= 0X50;   //设置通信方式为模式一，允许接收
	TMCON |= 0X02;
	TH1 = (Freq*1000000/baud)>>8;	  //波特率为T1的溢出时间；
	TL1 = Freq*1000000/baud;
	TR1 = 0;
	ET1 = 0;
	EUART = 1;     //开启Uart0中断	
}

static void Send_byte(unsigned char Byte)
{
	SBUF = Byte;
	while(!UartSendFlag);
	UartSendFlag = 0;
}

static unsigned char Send_Data(PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0;i < BUF_TX_SIZE;i ++)
	{
		Send_byte(p->Buf[i]);
	}
	return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_DATA)
{
	PROTOCOL_TX buf;
	memset(&buf,0,sizeof(buf));
	buf.Data0_Format.ADDR = addr;
	buf.Data0_Format.ID      = id;
	buf.Data0_Format.DATA1 = Hight(TX_DATA);
	buf.Data0_Format.DATA2 = Low(TX_DATA);
	buf.Data0_Format.CHECKSUM = (unsigned char)(buf.Data0_Format.ADDR + buf.Data0_Format.ID + buf.Data0_Format.DATA1 + buf.Data0_Format.DATA2);
	buf.Data0_Format.STOP1 = 0X0D;
	buf.Data0_Format.STOP2 = 0X0A;
	return Send_Data(&buf);
}

unsigned char IF_REV_ALL(void)
{
	if(Rev_Num & 0X80)
	{
             Rev_Num = 0x00;
	      return 1;
	}
	else
	{
		return 0;
	}
}

void Rev_Data_Handle(void)
{
	Rev_Data = SBUF;
	if((Rev_Num & 0x80) == 0)
	{
		if(Rev_Num & 0x40)
		{
			if(Rev_Data == 0x0a)
			{
				Rev_Num |= 0x80;
			}
			else
			{
				Rev_Num &= 0x00;
			}
		}
		else
		{
			if(Rev_Data == 0x0d)
			{
				Rev_Num |= 0x40;
			}
			else
			{
				Rev_String[Rev_Num] = Rev_Data;
				Rev_Num ++;
				if(Rev_String[0] != 0xfa)
				{
					Rev_Num &= 0x00;
				}
				if(Rev_Num > REV_BUF_SIZE)
				{
					Rev_Num &= 0x00;
				}
			}
		}
	}
}








