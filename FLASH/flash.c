#include "flash.h"

static void Flash_unlock(void){
	HAL_FLASH_Unlock();
}

static void Flash_lock(void){
	HAL_FLASH_Lock();
}

void Flash_earse_pages(uint32_t NbPages,uint32_t PageAddress){
	FLASH_EraseInitTypeDef earse;
	uint32_t page_error;
	earse.Banks=1;
	earse.PageAddress=PageAddress;
	earse.TypeErase=0x00U;
	earse.NbPages=NbPages;
	Flash_unlock();
	HAL_FLASHEx_Erase(&earse,&page_error);
	Flash_lock();
}

void Flash_Write(uint32_t address,uint8_t *data,uint16_t size){
	uint16_t data_w;
	Flash_unlock();
	for(uint8_t i=0;i<size;i=i+2)
	{
		data_w=(uint16_t)*(data+i+1)<<8;
		data_w|=*(data+i);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address+i,data_w);
	}
	Flash_lock();
}

void Flash_Read(uint32_t address,uint8_t *data,uint16_t size){
	for(uint8_t i=0;i<size;i+=2)
	{
		//uint8_t buffer=*(__IO uint32_t *)address+i;
		//*(data+i)=buffer;
		uint16_t buffer=*(__IO uint32_t *)address+i;
		*(data+i)=buffer;
		*(data+i+1)=buffer>>8;
	}
	
}
