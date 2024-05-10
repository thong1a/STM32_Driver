#include "button.h"
void BUTTON_Init(BUTTON_Name* Button, GPIO_TypeDef* BUTTON_PORT, uint16_t BUTTON_Pin)
{
		Button->BUTTON_PORT=BUTTON_PORT;
		Button->BUTTON_Pin=BUTTON_Pin;
}
BUTTON_STATE Button_read(BUTTON_Name *button)
{
		static uint32_t last_time;
		button->State=NO_CLICK;
		last_time=HAL_GetTick();
		if(Input_Button(button)!=button->pin_state)
		{
				button->pin_state=Input_Button(button);
				last_time=HAL_GetTick();
		}
		if(HAL_GetTick()-last_time>DEBOUND_TIME)
		{
				if(button->pin_state==GPIO_PIN_SET)
				{
						button->isPress=1;
						button->State=SINGLE_CLICK;
				}
				else
				{
						button->isPress=0;
						button->State=NO_CLICK;
				}
		}
		return button->State;
}