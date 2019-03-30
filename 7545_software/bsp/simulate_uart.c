#include "simulate_uart.h"
#include <string.h>
#include "timeout.h"

enum{
	UART_START = 0,
	UART_DATA,
	UART_STOP
};

static XDATA unsigned char rx_rev_byte_cnt[S_MAX_UART_NUM];
static XDATA unsigned char rx_sta[S_MAX_UART_NUM];
static XDATA unsigned char rx_data[S_MAX_UART_NUM][S_MAX_REV_DATA];	
static XDATA unsigned char rx_start_cnt[S_MAX_UART_NUM];
static XDATA unsigned char rx_bit_cnt[S_MAX_UART_NUM];
static XDATA unsigned char rx_byte_cnt[S_MAX_UART_NUM];
static volatile unsigned char rx_user_data[S_MAX_UART_NUM];
static XDATA TIMEOUT_PARA rx_timeout[S_MAX_UART_NUM];
static XDATA unsigned char rx_offline_flag[S_MAX_UART_NUM];

static unsigned char read_rx_pin(unsigned char pin)
{
	if(pin == 0){
		return READ_RX1_PIN;
	}else if(pin == 1){
		return READ_RX2_PIN;
	}else{
		return 0;
	}
}

void simulate_uart_init(void)
{
	int i;
	CLR_REG_CON(4,4);
	CLR_REG_CON(1,2);
	for(i = 0; i < S_MAX_UART_NUM;i ++){
		rx_rev_byte_cnt[i] = 0;
		rx_sta[i] = UART_START;
		rx_data[i][0] = rx_data[i][1] = rx_data[i][2] = 0;
		rx_start_cnt[i] = 0;
		rx_bit_cnt[i] = 0;
		rx_byte_cnt[i] = 0;
		rx_offline_flag[i] = 0;
		TimeOut_Record(&rx_timeout[i], S_UART_TIMEOUT);
	}	
}

void simulate_uart_rx_handle(void)
{
	int i;
	for(i = 0; i < S_MAX_UART_NUM;i ++){
		switch(rx_sta[i]){
			case UART_START:{
				if(!read_rx_pin(i)){
					if(rx_start_cnt[i] ++ >= S_START_DET_CNT){
						rx_sta[i] = UART_DATA;
						rx_start_cnt[i] = 0;
						if(rx_rev_byte_cnt[i] == 0){
							rx_data[i][0] = rx_data[i][1] = rx_data[i][2] = 0;
						}
					}
				}else{
					rx_start_cnt[i] = 0;
				}
				rx_byte_cnt[i]  = 0;
				break;
			}

			case UART_DATA:{
				if(rx_byte_cnt[i] ++ >= S_DATA_DET_CNT){
					rx_byte_cnt[i] = 0;
					rx_bit_cnt[i] ++;
					if(read_rx_pin(i)){
						rx_data[i][rx_rev_byte_cnt[i]] |= 1<<(rx_bit_cnt[i] -1);
					}
				
					if(rx_bit_cnt[i] >= S_DATA_BIT_CNT){
						rx_byte_cnt[i] = 0;					
						rx_rev_byte_cnt[i] ++;

						if(rx_data[i][0] != S_UART_START){
							rx_rev_byte_cnt[i] = 0;
						}
						rx_sta[i] = UART_STOP;
						rx_bit_cnt[i] = 0;
						
						if(rx_rev_byte_cnt[i] >= S_MAX_REV_DATA){
							unsigned char crc =0;
							rx_rev_byte_cnt[i]  = 0;					
							crc = rx_data[i][0] + rx_data[i][1] ;		
							if(crc == rx_data[i][2]){
								rx_user_data[i] = rx_data[i][1];
								rx_offline_flag[i] = False;
								TimeOut_Record(&rx_timeout[i], S_UART_TIMEOUT);
								if(i == 0){
									//P22 =!P22;								
								}else if(i == 1){
									//P20 = !P20;
								}
							}
						}					
					}
				}
				break;
			}

			case UART_STOP:{
				rx_sta[i] = UART_START;
				rx_start_cnt[i] = 0;
				break;
			}
			default:
				break;
		}
	}
}

unsigned char simulate_get_userdata(unsigned char rx_port)
{
	if(TimeOutDet_Check(&rx_timeout[rx_port])){
		return NO_KEY;
	}
	return rx_user_data[rx_port];
}

