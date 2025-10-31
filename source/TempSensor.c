#include "TempSensor.h"

float Temp1_Goal = 0;
float Temp1_Actual = 0;
float Temp2_Goal = 0;
float Temp2_Actual = 0;

void Temp_SetupAll(void){
	Temp_SetConfigurationReg(TEMP1_ADDRESS, 0b0000000000101100);
	Temp_SetConfigurationReg(TEMP2_ADDRESS, 0b0000000000101100);
}

void Temp_Write(uint8_t _SlaveAddress, uint8_t _RegisterAddress, char _message[], uint8_t _Length){
	I2C_Write(_SlaveAddress, _RegisterAddress, _message, _Length);
}

void Temp_Read(uint8_t _SlaveAddress, uint8_t _RegisterAddress, uint8_t _Length){
	I2C_Read(_SlaveAddress, _RegisterAddress, _Length);
}

void Temp_Shutdown(uint8_t SlaveAddress){
	Temp_SetConfigurationReg(SlaveAddress, 0b0000010000101100);
}

void Temp_SetConfigurationReg(uint8_t _SlaveAddress, uint16_t Config){
	char message[2] = {Config >> 8, Config & 0xFF}; //Sets message to change config register based on passed parameter
	Temp_Write(_SlaveAddress, 0x01, message, 2);
}

void Temp_TriggerTempConv(void){
//	Temp_Read(0x01, 2);
//	uint8_t MSB = I2C_Master -> ReadBuff[0];
//	MSB = (MSB & (~0x0C)) + 0x0C;
//	char message[2] = {MSB, I2C_Master -> ReadBuff[1]};
//	Temp_Write(0x01, message, 2); //Write to certain register to trigger a temp measurement
//	TempSens -> Temp_IsTriggered = true; //Set variable to show that a temperature measurement has been triggered
}

float Temp_ReadTemperature(uint8_t _SlaveAddress){
	Temp_Read(_SlaveAddress, 0x00, 2);
	float TempConv = ((I2C_Master -> ReadBuff[0] << 8) + (I2C_Master -> ReadBuff[1])) * 0.0078125; //Convert digital data to celcius
	return TempConv;
}
