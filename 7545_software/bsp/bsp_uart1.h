#ifndef _BSP_UART1_H_
#define _BSP_UART1_H_

#include "sc92f754x_c.h"

#define     UART1_BUF_SIZE       7
#define     UART1_REV_BUF_SIZE      7

#define     UART1_Hight(x)         (((x)>>8)&0xff)
#define     UART1_Low(x)           ((x)&0xff)

#define     UART1_Get_32Bit(x,y)     ((((x)<<8)|y)&0xffff)

typedef struct
{
	unsigned char UART1_ADDR1;
	unsigned char UART1_ID1;
	unsigned char UART1_DATA1;
	unsigned char UART1_DATA2;
	unsigned char UART1_CHECKSUM;
	unsigned char UART1_STOP1;
	unsigned char UART1_STOP2;
}
UART1_DATA_FORMAT_TX;

typedef union
{
	unsigned char UART1_Buf[UART1_BUF_SIZE];
	UART1_DATA_FORMAT_TX Uart1_Data_Format;
}
UART1_PROTOCOL_TX;



void Uart1_Init(unsigned char Freq,unsigned int baud);
unsigned char Uart1_Protocol_Send(unsigned char Uart1_Addr,unsigned char Uart1_Id,unsigned int Uart1_TX_Data);

unsigned char Uart1_IF_REV_ALL(void);
void Uart1_Serial_Handle(void);





#endif


