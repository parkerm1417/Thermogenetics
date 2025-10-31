#include "Flash.h"

flash_config_t flashConfig;

uint32_t Flash_Read(uint32_t *address)
{
    return *address;
}

void Flash_Write(uint32_t *data, uint32_t len)
{
	FLASH_Init(&flashConfig);
    // Program new data
    FLASH_Program(&flashConfig, FLASH_USER_DATA_ADDR, data, len);
}

void Flash_Clear(void){
    FLASH_Init(&flashConfig); // Initialize Flash driver

    // Erase the sector before writing (1 KB sector)
    FLASH_Erase(&flashConfig, FLASH_USER_DATA_ADDR, 1024, kFLASH_ApiEraseKey);
}
