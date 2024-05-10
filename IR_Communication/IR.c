#include "IR.h"

uint16_t timeout2=0;
uint16_t timeout1=0;
uint8_t is_firstcapture=1;
uint16_t distance=0;
uint8_t bit,flag=0;
uint32_t data,code;
#define Start_signal 130  //13.5ms
#define Start_singnal_end  150 // 1 lan dem la 100us
#define logic_bit_0 11


void IR_Init(TIM_HandleTypeDef *tim, uint32_t channel){
	Tim=tim;
	Channel=channel;
	HAL_TIM_IC_Start_IT(Tim,Channel);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	timeout2=HAL_TIM_ReadCapturedValue(Tim,Channel);
	if(timeout2>timeout1)
	distance=timeout2-timeout1;
	else distance=65536-timeout1+timeout2;
	timeout1=timeout2;
	if(distance>=Start_signal&&distance<=Start_singnal_end) // start singal
	{
		bit=0;
		data=0;
		flag++;
	}
	else if(distance>=11&&distance<=18&&bit<32) 
	{
		
		data&=~(1<<bit); // ghi bit 0
		bit++;
	}
	else if(distance>=21&&distance<=28&&bit<32)
	{
		data|=1<<bit;
		bit++;
	}
	if(bit==32)
	{
		code=data;
	}
	
}

void IR_Read(uint32_t *data1){
	if(bit>=32){
		*data1=code;
	}
	
}
