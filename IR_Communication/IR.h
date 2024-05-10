#ifndef _IR_H
#define _IR_H
#include "stm32f1xx_hal.h"
static TIM_HandleTypeDef *Tim;
static uint32_t Channel;
void IR_Init(TIM_HandleTypeDef *tim, uint32_t channel);
void IR_Read(uint32_t *data);
#endif
