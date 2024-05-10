#ifndef _DHT_H
#define _DHT_H
#include "stm32f1xx_hal.h"
#define Error_data 60
typedef struct {
	GPIO_TypeDef *Port;
	uint16_t pin;
	uint8_t temp;
	uint8_t humid;
}DHT_Typedef;
typedef enum{
	DHT_Time_error=500,
	DHT_CRC_error=600,
	DHT_OK=700
}DHT_Status;
static TIM_HandleTypeDef *htim;
static void DHT_Delay_ms(uint32_t time);
static void DHT_Delay_us(uint32_t time);
static void config_output(DHT_Typedef *dht);
static void config_input(DHT_Typedef *dht);
void DHT_Init(DHT_Typedef *dht,GPIO_TypeDef * port,uint16_t pin,TIM_HandleTypeDef *tim);
static uint8_t DHT_ReadBit(DHT_Typedef *dht);
static void DHT_WriteBit(DHT_Typedef *dht,GPIO_PinState state);
static void DHT_Start(DHT_Typedef *dht);
static DHT_Status check_responde(DHT_Typedef *dht);
static uint8_t dht_read(DHT_Typedef *dht);
void get_data(DHT_Typedef *dht);
static DHT_Status check_crc(uint8_t *data);

#endif
