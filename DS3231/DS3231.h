#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f1xx_hal.h"

#define DS3231_ADDRESS 0x68<<1
#define DS3231_ADDRESS_SEC 0x00
#define DS3231_ALARM_MIN    (0x0B)
typedef struct
{
	I2C_HandleTypeDef* I2C;
	uint8_t Hours;
	uint8_t Min;
	uint8_t Sec;
	uint8_t Date;
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;
}DS3231_TypedefHandle;

void DS3231_Init(DS3231_TypedefHandle *DS32,I2C_HandleTypeDef* hic);
void DS3231_SetTime(DS3231_TypedefHandle *DS32,uint8_t hours,uint8_t min, uint8_t sec, uint8_t day,uint8_t date, uint8_t month, uint8_t year);
void DS3231_GetTime(DS3231_TypedefHandle *DS32);
//void DS3231_SetAlarm(DS3231_TypedefHandle *DS32,uint8_t date,uint8_t hours,uint8_t min);
//uint8_t DS3231_CheckAlarm(DS3231_TypedefHandle *DS32);
//void WriteBuffer(DS3231_TypedefHandle *DS32,uint16_t MemAddress,uint8_t *pData, uint16_t Size);
//void ReadBuffer(DS3231_TypedefHandle *DS32,uint16_t MemAddress,uint8_t *pData, uint16_t Size);
#endif
