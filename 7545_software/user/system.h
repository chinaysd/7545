#ifndef _SYSTEM_H_
#define _SYSTEM_H_


#include "SC92F754X_C.h"





#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_timer.h"
#include "TimeOut.h"
#include "bsp_uart0.h"
#include "string.h"
#include "bsp_uart1.h"
#include "bsp_pwm.h"
#include "simulate_uart.h"





















void System_Init(void);
void System_Handle(void);



#endif





