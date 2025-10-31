#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include "stdint.h"
#include "fsl_common.h"

#include "I2C_Master.h"

#define TEMP1_ADDRESS 0x49
#define TEMP2_ADDRESS 0x48

extern float Temp1_Goal;
extern float Temp1_Actual;
extern float Temp2_Goal;
extern float Temp2_Actual;


void Temp_SetupAll(void); //Fully initialize the temperature sensor

void Temp_Write(uint8_t _SlaveAddress, uint8_t _RegisterAddress, char _message[], uint8_t _Length);

void Temp_Read(uint8_t _SlaveAddress, uint8_t _RegisterAddress, uint8_t _Length);

void Temp_Shutdown(uint8_t SlaveAddress);

void Temp_SetConfigurationReg(uint8_t _SlaveAddress, uint16_t Config); //Change the configuration of the temperature sensor

void Temp_TriggerTempConv(void); //Trigger a temperature measurement by the temperature sensor

float Temp_ReadTemperature(uint8_t _SlaveAddress); //Read the measured temperature from the temp sensor with the MCU

#endif /* HEADER_AND_C_FILES_TEMPSENSOR_H_ */
