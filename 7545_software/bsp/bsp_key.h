#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_


#include "sc92f754x_c.h"


#define KEYF_ENABLE     1
#define KEYF_DISABLE    0

#define KEYR_ENABLE     1
#define KEYR_DISABLE    0




#define KEY1_PORT      P4
#define KEY1_PIN        P43

#define KEYD_STATUS     0
#define KEYU_STATUS     1




void Key_Init(void);
unsigned char Key_Down(void);




#endif

