#ifndef _BSP_LED_H_
#define _BSP_LED_H_


#include "SC92F754X_C.H"

#define LED1_PORT       P4
#define LED1_PIN          P41
#define LED1_SET(X)     ((X)?(LED1_PIN=1):(LED1_PIN=0))

#define LED2_PORT       P4
#define LED2_PIN          P42
#define LED2_SET(X)      ((X)?(LED2_PIN=1):(LED2_PIN=0))







void Led_Init(void);





#endif
