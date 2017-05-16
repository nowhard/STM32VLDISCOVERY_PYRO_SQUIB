#ifndef DIG_POT_H
#define DIG_POT_H
#include "stm32f1xx_hal.h"


#define I2C_POT_NUM			4

typedef enum
{
	DIG_POT_1=0,
	DIG_POT_2=1,
	DIG_POT_3=2,
	DIG_POT_4=3,
} enDigPot;


void DigPot_Init(void);
void DigPot_SetValue(enDigPot DigPot, uint8_t value);

#endif