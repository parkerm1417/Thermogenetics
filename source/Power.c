#include "Power.h"

void Power_Setup(void){
	SMC->PMPROT = 0b00100000; //Enables very low power modes, https://www.nxp.com/files-static/32bit/doc/ref_manual/KL02P32M48SF0RM.pdf, PG.167
	SCB->SCR = 0x00000006; //Enables deep sleep using WFI and on exiting interrupt handler, https://developer.arm.com/documentation/100235/0004/the-cortex-m33-peripherals/system-control-block/system-control-register?lang=en
	SMC->PMCTRL = 0b01000010; //Tells MCU to use VLPR in Run mode and VLPS in Sleep Mode, https://www.nxp.com/files-static/32bit/doc/ref_manual/KL02P32M48SF0RM.pdf, PG.169

}

void Power_GoToSleep(void){
	__asm("WFI"); //assembly code for Wait For Interrupt, this puts the MCU to sleep/deep sleep depending on settings set in SleepMode_Setup
}
