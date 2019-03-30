#ifndef SYS_CONFIG_H_
#define SYS_CONFIG_H_

#include "SC92F754x_C.H"
#include "data_type.h"

#define SYS_FRE_SET					4000000

#ifndef ON
#define ON  1
#endif

#ifndef OFF
#define OFF 0
#endif

#define XDATA						xdata

#define IO_OUT						1
#define IO_IN							0

#define Get_Low(x)					((x) & 0XFF)
#define Get_High(x)					(((x) >> 8) & 0XFF)
#define Get_32bit(x,y)					((((x) << 8) | (y)) & 0XFFFF)


/**
	@brief:IO 控制寄存器设置
*/
#define SET_REG_CON(X,Y)				(P##X##CON |= ((1)<<(Y)))
#define CLR_REG_CON(X,Y)				(P##X##CON &= ~((1)<<(Y)))

/**
	@brief:IO 上拉设置
*/
#define SET_IO_PU(X,Y)				(P##X##PH |= ((1)<<(Y)))
#define CLR_IO_PU(X,Y)				(P##X##PH &= ~((1)<<(Y)))

/**
	@brief:喂狗功能
*/
#define SYS_ENABLE_WDT
#define CLEAR_WDT()					(WDTCON  = 0x10)	


#define UART0_ENABLE					
#define UART1_ENABLE

/**
	@brief:选择复位方式
*/
#define PUSH_TO_RESET				0		/*<按下复位，松手也继续复位>*/
#define PRESS_RESET					1		/*<按下复位，松手停止复位>*/
#define ONE_KEY_RESET_TYPE			PRESS_RESET

/**
	@brief:功能使能区
*/
#define PUSHROD_BACK_ENABLE
#define PUSHROD_HEAD_ENABLE
#define PUSHROD_LUMBAR_ENABLE
#ifdef PUSHROD_BACK_ENABLE
	#ifndef PUSH_ENABLE
	#define PUSH_ENABLE
	#endif
#endif
#ifdef PUSHROD_HEAD_ENABLE
	#ifndef PUSH_ENABLE
	#define PUSH_ENABLE
	#endif
#endif
#ifdef PUSHROD_LUMBAR_ENABLE
	#ifndef PUSH_ENABLE
	#define PUSH_ENABLE
	#endif
#endif
#define RESET_ENABLE
#define WARN_ENABLE
//#define MASSAGE_ENABLE
#define LIGHT_ENALBE









#endif
