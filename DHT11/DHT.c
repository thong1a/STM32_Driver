#include "DHT.h"

static void config_input(DHT_Typedef *dht){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	
	GPIO_InitStruct.Pin = dht->pin;
	
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	
  HAL_GPIO_Init(dht->Port, &GPIO_InitStruct);
}

static void config_output(DHT_Typedef *dht){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = dht->pin;
	
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
  HAL_GPIO_Init(dht->Port, &GPIO_InitStruct);
}

static void DHT_Delay_ms(uint32_t time){
	HAL_Delay(time);
}

static void DHT_Delay_us(uint32_t time){
	__HAL_TIM_SET_COUNTER(htim,0);
	while(__HAL_TIM_GET_COUNTER(htim)<time);
}

void DHT_Init(DHT_Typedef *dht,GPIO_TypeDef * port,uint16_t pin,TIM_HandleTypeDef *tim){
	dht->Port=port;
	dht->pin=pin;
	htim=tim;
}

static void DHT_Start(DHT_Typedef *dht){
	config_output(dht);
	//HAL_GPIO_WritePin(dht->Port,dht->pin,0);
	DHT_WriteBit(dht,0);
	DHT_Delay_ms(18);
//	HAL_GPIO_WritePin(dht->Port,dht->pin,1);
	DHT_WriteBit(dht,1);
	DHT_Delay_us(20);
	config_input(dht);
}

static DHT_Status check_responde(DHT_Typedef *dht){
	DHT_Status res=0;
	DHT_Delay_us(40);
//	if(!(HAL_GPIO_ReadPin(dht->Port,dht->pin)))
	if(!(DHT_ReadBit(dht)))
	{
		DHT_Delay_us(80);
		//if((HAL_GPIO_ReadPin(dht->Port,dht->pin))) 
		if(DHT_ReadBit(dht))
		res=DHT_OK;
		else res=DHT_Time_error;
	}	
	//while((HAL_GPIO_ReadPin(dht->Port,dht->pin)));
	while(DHT_ReadBit(dht));
	return res;
}

static uint8_t dht_read(DHT_Typedef *dht){
	uint8_t data,bit;
	for(bit=0;bit<8;bit++)
	{
		//while(!(HAL_GPIO_ReadPin(dht->Port,dht->pin)));
		while(!(DHT_ReadBit(dht)));
		DHT_Delay_us(40);
		//if(!(HAL_GPIO_ReadPin(dht->Port,dht->pin)))
		if(!(DHT_ReadBit(dht)))
		{
			data&=~(1<<(7-bit));
		}
		else data|=(1<<(7-bit));
		//while((HAL_GPIO_ReadPin(dht->Port,dht->pin)));
		while(DHT_ReadBit(dht));
	}
	return data;	
}

void get_data(DHT_Typedef *dht){
	uint8_t temp1,temp2,rh1,rh2,checksum;
	DHT_Start(dht);
	if(check_responde(dht)==DHT_Time_error)
	{
		dht->temp=Error_data;
		dht->humid=Error_data;
	}
	rh1=dht_read(dht);
	rh2=dht_read(dht);
	temp1=dht_read(dht);
	temp2=dht_read(dht);
	checksum=dht_read(dht);
	if(checksum==rh1+rh2+temp1+temp2)
	{
		dht->temp=temp1;
		dht->humid=rh1;
	}
	else 
	{
		dht->temp=Error_data;
		dht->humid=Error_data;
	}
}

static uint8_t DHT_ReadBit(DHT_Typedef *dht){
	return HAL_GPIO_ReadPin(dht->Port,dht->pin);
}

static void DHT_WriteBit(DHT_Typedef *dht,GPIO_PinState state){
	HAL_GPIO_WritePin(dht->Port,dht->pin,state);
}

static DHT_Status check_crc(uint8_t *data){
	if(data[4]==data[0]+data[1]+data[2]+data[3])
		return DHT_OK;
	else return DHT_CRC_error;
}