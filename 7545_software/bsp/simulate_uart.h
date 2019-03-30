#ifndef SIMULATE_UART_H_
#define SIMULATE_UART_H_

#include "sys_config.h"

#define S_MAX_REV_DATA				3
#define S_MAX_UART_NUM				2

#define S_UART_PORT0					0
#define S_UART_PORT1					1

#define S_UART_RX1_PORT				P44
#define S_UART_RX2_PORT				P12

#define READ_RX1_PIN					S_UART_RX1_PORT
#define READ_RX2_PIN					S_UART_RX2_PORT

#define S_UART_START					0x55
#define S_UART_TIMEOUT				1000

#define S_START_DET_CNT				1
#define S_DATA_DET_CNT				2
#define S_DATA_BIT_CNT				8

#define NO_KEY						0X00

void simulate_uart_init(void);

void simulate_uart_rx_handle(void);

unsigned char simulate_get_userdata(unsigned char rx_port);

#endif

