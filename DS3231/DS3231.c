#include "DS3231.h"

static uint8_t B2D(uint8_t data)
{
	return (data>>4)*10+ (data&0x0f);
}

static uint8_t D2B(uint8_t data)
{
	return (data/10)<<4|(data%10);
}
void DS3231_Init(DS3231_TypedefHandle *DS32,I2C_HandleTypeDef* hic){
	DS32->I2C=hic;
}

void DS3231_SetTime(DS3231_TypedefHandle *DS32,uint8_t hours,uint8_t min, uint8_t sec, uint8_t day,uint8_t date, uint8_t month, uint8_t year){
	uint8_t buffer[8];
	buffer[0]=0x00;
	buffer[1]=D2B(sec);
	buffer[2]=D2B(min);
	buffer[3]=D2B(hours);
	buffer[4]=D2B(day);
	buffer[5]=D2B(date);
	buffer[6]=D2B(month);
	buffer[7]=D2B(year);
	HAL_I2C_Master_Transmit(DS32->I2C,DS3231_ADDRESS,buffer,8,100);
//	WriteBuffer(DS32,DS3231_ADDRESS_SEC,buffer,7);
	
	//	buffer[0]=D2B(sec);
	//buffer[1]=D2B(min);
//	buffer[2]=D2B(hours);
	//buffer[3]=D2B(day);
	//buffer[4]=D2B(date);
	//buffer[5]=D2B(month);
	//buffer[6]=D2B(year);
	//HAL_I2C_Master_Transmit(DS32->I2C,DS3231_ADDRESS,buffer,8,1000);
//	HAL_I2C_Mem_Write(DS32->I2C,DS3231_ADDRESS,DS3231_ADDRESS_SEC,I2C_MEMADD_SIZE_8BIT,buffer,7,1000);
}

void DS3231_GetTime(DS3231_TypedefHandle *DS32){
	uint8_t buffer[7];
	HAL_I2C_Master_Transmit(DS32->I2C,DS3231_ADDRESS,0x00,1,100);
	HAL_I2C_Master_Receive(DS32->I2C,DS3231_ADDRESS,buffer,7,100);
//	ReadBuffer(DS32,DS3231_ADDRESS_SEC,buffer,7);
	DS32->Sec=B2D(buffer[0]);
	DS32->Min=B2D(buffer[1]);
	DS32->Hours=B2D(buffer[2]);
	DS32->Day=B2D(buffer[3]);
	DS32->Date=B2D(buffer[4]);
	DS32->Month=B2D(buffer[5]);
	DS32->Year=B2D(buffer[6]);
}

//void DS3231_SetAlarm(DS3231_TypedefHandle *DS32,uint8_t date,uint8_t hours,uint8_t min){
//	uint8_t buffer[3];
//	buffer[0]=D2B(min);
//	buffer[1]=D2B(hours);
//	buffer[2]=D2B(date);
//	HAL_I2C_Mem_Write(DS32->I2C,DS3231_ADDRESS,DS3231_ALARM_MIN,I2C_MEMADD_SIZE_8BIT,buffer,3,1000);
//}
//
//uint8_t DS3231_CheckAlarm(DS3231_TypedefHandle *DS32){
//	uint8_t buffer[3],i;
//	HAL_I2C_Mem_Read(DS32->I2C,DS3231_ADDRESS,DS3231_ALARM_MIN,I2C_MEMADD_SIZE_8BIT,buffer,3,1000);
//	for(i=0;i<3;i++)
//	{
//		buffer[i]=buffer[i]>>7;
//		if((buffer[i]&0x01)!=0)
//			
//		 return 0;
//	}
//	if(i==3)
//	return 1;
//	else 
//		return 0;
//}
//void WriteBuffer(DS3231_TypedefHandle *DS32,uint16_t MemAddress,uint8_t *pData, uint16_t Size){
//	HAL_I2C_Mem_Write(DS32->I2C,DS3231_ADDRESS,MemAddress,I2C_MEMADD_SIZE_8BIT,pData,Size,1000);
//}
//
//void ReadBuffer(DS3231_TypedefHandle *DS32,uint16_t MemAddress,uint8_t *pData, uint16_t Size){
//	HAL_I2C_Mem_Read(DS32->I2C,DS3231_ADDRESS,MemAddress,I2C_MEMADD_SIZE_8BIT,pData,Size,1000);
//}
