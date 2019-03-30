#ifndef _BSP_UART0_H_
#define _BSP_UART0_H_

#include "sc92f754x_c.h"

#define UART0_Freq       16
#define UART0_Baud      9600

#define UART1_Freq       16
#define UART1_Baud      9600

#define BUF_TX_SIZE      7
#define REV_BUF_SIZE    7



#define Hight(x)             ((x>>8)&0xff)
#define Low(x)               ((x)&0xff)

#define Get_32Bit(x,y)    (((x<<8)|y)&0xffff)


typedef struct
{
	unsigned char ADDR;
       unsigned char ID;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM;
	unsigned char STOP1;
	unsigned char STOP2;
}
DATA0_FORMAT_TX;

typedef union
{
	unsigned char Buf[BUF_TX_SIZE];
       DATA0_FORMAT_TX Data0_Format;	
}
PROTOCOL_TX;






void Uart0_Init(unsigned char Freq,unsigned int baud);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_DATA);
unsigned char IF_REV_ALL(void);
void Rev_Data_Handle(void);


#endif




