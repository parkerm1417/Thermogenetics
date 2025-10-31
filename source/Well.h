#ifndef WELL_H_
#define WELL_H_

#include "stdint.h"
#include "board.h"
#include "pin_mux.h"
#include "TempSensor.h"

struct Well{
	bool WellState;
	uint8_t OnTime;
	uint16_t Cycles;
	uint8_t TempAddress;
	float TempGoal;
	GPIO_Type *GPIOBase;
	uint32_t GPIOPin;
};

extern struct Well Wells[2];

void Well_Heat(struct Well _Well);

void Well_Cool(struct Well _Well);

#endif /* WELL_H_ */
