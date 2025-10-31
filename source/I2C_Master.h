#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include "fsl_i2c.h"
#include "board.h"


#define I2C_BASE I2C0 //Tells board which I2C network we will use
#define I2C_CLK_SPD CLOCK_GetFreq(I2C0_CLK_SRC) //Sets I2C speed
#define I2C_MAX_LEN 64U //Sets maximum length of a message


typedef struct _I2Cbus{
	i2c_master_config_t Config; //I2C configuration
	i2c_master_transfer_t Xfer; //I2C Transfer Parameters
	uint8_t ReadBuff[I2C_MAX_LEN]; //Buffer to store data when an I2C read occurs
} I2Cbus;

extern I2Cbus I2Cstruct; //Instance of I2Cbus structure
extern I2Cbus* I2C_Master; //pointer to instance of I2C bus structure

//Setup the default settings for an I2C network
void I2C_GetDefaultSettings(I2Cbus *I2C);

//Configures all I2C related things for this project
void I2C_SetupAll();

void I2C_Write(uint8_t _SlaveAddress, uint16_t _RegisterAddress, char _message[], uint8_t _length);

void I2C_Read(uint8_t _SlaveAddress, uint16_t _RegisterAddress, uint8_t _length);
#endif /* HEADER_AND_C_FILES_I2C_MASTER_H_ */
