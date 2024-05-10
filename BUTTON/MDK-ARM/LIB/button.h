#ifndef		_BUTTON_H
#define		_BUTTON_H
#include "stm32f1xx_hal.h"
#define DEBOUND_TIME 50
#define SINGLE_CLICK_TIME 1000
#define DOUBLE_CLICK_TIME 300
#define Input_Button(button)			HAL_GPIO_ReadPin(button->BUTTON_PORT,button->BUTTON_Pin)
typedef enum
{
	NO_CLICK 		 = 0x00,
  SINGLE_CLICK = 0x01,
	DOUBLE_CLICK = 0x02,
	LONGCLICK_1S = 0x03
}BUTTON_STATE;
typedef struct {
	GPIO_TypeDef* BUTTON_PORT;
	uint16_t BUTTON_Pin;
	GPIO_PinState	pin_state;
	BUTTON_STATE State;
	uint8_t  isPress;
	uint16_t timePress;
	uint16_t timeDouble;
}BUTTON_Name;
void BUTTON_Init(BUTTON_Name* Button, GPIO_TypeDef* BUTTON_PORT, uint16_t BUTTON_Pin);
BUTTON_STATE Button_read(BUTTON_Name *button);

#endif