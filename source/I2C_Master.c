#include "I2C_Master.h"

I2Cbus I2Cstruct;
I2Cbus* I2C_Master = &I2Cstruct;

void I2C_GetDefaultSettings(I2Cbus *I2C){
	//Setup and initialize I2C network
	I2C_MasterGetDefaultConfig(&I2C -> Config);
	I2C_MasterInit(I2C_BASE, &I2C -> Config, I2C_CLK_SPD);

	//Set initial parameters for the I2C transfer configuration
	I2C -> Xfer.slaveAddress = 0x00;
	I2C -> Xfer.direction = kI2C_Write;
	I2C -> Xfer.subaddress = (uint32_t) 0x01;
	I2C -> Xfer.subaddressSize = 1;
	I2C -> Xfer.data = I2C -> ReadBuff;
	I2C -> Xfer.dataSize = I2C_MAX_LEN;
	I2C -> Xfer.flags = kI2C_TransferDefaultFlag;
}

void I2C_SetupAll(){
	I2C_GetDefaultSettings(I2C_Master);
}

void I2C_Write(uint8_t _SlaveAddress, uint16_t _RegisterAddress, char _Message[], uint8_t _Length){
	//Reinitialize I2C network
	I2C_GetDefaultSettings(I2C_Master);

	//Make an array that is the length of the message parameter, then copy the message parameter to the array memory
	uint8_t WriteBuff[_Length];
	memcpy(WriteBuff,_Message,_Length);

	//Set I2C transfer parameters for this write action specifically
	I2C_Master -> Xfer.slaveAddress = _SlaveAddress;
	I2C_Master -> Xfer.direction = kI2C_Write;
	I2C_Master -> Xfer.subaddressSize = 1;
	I2C_Master -> Xfer.subaddress = _RegisterAddress;
	I2C_Master -> Xfer.dataSize = _Length;
	I2C_Master -> Xfer.data = WriteBuff;

	if(I2C_Master -> Xfer.slaveAddress == 0x53 || I2C_Master -> Xfer.slaveAddress == 0x57)
		I2C_Master -> Xfer.subaddressSize = 2;

	//Transfer the data
	I2C_MasterTransferBlocking(I2C_BASE, &I2C_Master -> Xfer);
}


void I2C_Read(uint8_t _SlaveAddress, uint16_t _RegisterAddress, uint8_t _Length){
	//Reinitialize I2C network
	I2C_GetDefaultSettings(I2C_Master);

	//Set specific I2C transfer parameters for this read action
	I2C_Master -> Xfer.slaveAddress = _SlaveAddress;
	I2C_Master -> Xfer.direction = kI2C_Read;
	I2C_Master -> Xfer.subaddressSize = 1;
	I2C_Master -> Xfer.subaddress = _RegisterAddress;
	I2C_Master -> Xfer.dataSize = _Length;
	I2C_Master -> Xfer.data = I2C_Master -> ReadBuff;

	if(I2C_Master -> Xfer.slaveAddress == 0x53 || I2C_Master -> Xfer.slaveAddress == 0x57)
		I2C_Master -> Xfer.subaddressSize = 2;

	//Read the data
	I2C_MasterTransferBlocking(I2C_BASE, &I2C_Master -> Xfer);
}
