#ifndef FLASH_H_
#define FLASH_H_

#include "fsl_flash.h"

#define FLASH_USER_DATA_ADDR  0x00007C00  // User storage location

extern flash_config_t flashConfig;  // Flash driver instance

uint32_t Flash_Read(uint32_t *address);

void Flash_Write(uint32_t *data, uint32_t len);

void Flash_Clear(void);
#endif /* FLASH_H_ */
