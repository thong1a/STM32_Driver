#ifndef _FLASH_H
#define _FLASH_H

#include "stm32f1xx_hal.h"


//void Flash_massearse(void);
void Flash_earse_pages(uint32_t NbPages,uint32_t PageAddress);
void Flash_Read(uint32_t address,uint8_t *data,uint16_t size);
void Flash_Write(uint32_t address,uint8_t *data,uint16_t size);
static void Flash_unlock(void);
static void Flash_lock(void);
#endif

