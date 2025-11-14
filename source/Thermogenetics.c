#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "Timer.h"
#include "TempSensor.h"
#include "Flash.h"
#include "Well.h"
#include "Downlink.h"
#include "Power.h"
#include "fsl_smc.h"
#include "crc32.h"
#include "SEGGER_RTT.h"

#define LED_GPIO BOARD_INITPINS_LED_GPIO
#define LED_PIN BOARD_INITPINS_LED_PIN

enum state{
	STARTUP,
	IDLE,
	TEMP_CTRL,
	PREPARE_DOWNLINK,
	DOWNLINK
};

uint8_t TransmissionArray[14] = {0};
int TransmittedBits = -3;
int BitCutoff = 0;
int Time0 = 0;
int Time1 = 0;
int Duration = 0;
int Seconds = 0;
bool SkipBit = 0;
uint8_t State = STARTUP;
float Temp1 = 0;
float Temp2 = 0;

int main(void) {
	BOARD_InitPins();
	Flash_Clear();
	BOARD_BootClockRUN();

	SEGGER_RTT_Init();
	SEGGER_RTT_printf(0, "\r\n=== RTT Debug ===\r\n");

	Well_Cool(Wells[0]);
	Well_Cool(Wells[1]);
	I2C_SetupAll();
	Timer_SetupAll();
	Power_Setup();
	Temp_SetupAll();

	uint32_t SavedData = 0;

    for(int i=0; i<2; i++){
		SavedData = Flash_Read((uint32_t *)(FLASH_USER_DATA_ADDR + (4*i)));
		if(SavedData != 0xFFFFFFFF){
			Wells[i].OnTime = (SavedData >> 16) & 0xFF;
			Wells[i].Cycles = (SavedData & 0xFFFF);
		}
    }
    SavedData = Flash_Read((uint32_t *)(FLASH_USER_DATA_ADDR + 8));
    if(SavedData != 0xFFFFFFFF){
    	Wells[0].TempGoal = (SavedData >> 16);
    	Wells[0].TempGoal /= 10;
    	Wells[1].TempGoal = (SavedData & 0xFFFF);
    	Wells[1].TempGoal /= 10;
    }
    State = TEMP_CTRL;

	Timer_Start();
	GPIO_PortClear(LED_GPIO, 1 << LED_PIN);
	for(uint32_t i=0; i<1600; i++){
	}
	GPIO_PortSet(LED_GPIO, 1 << LED_PIN);
    SEGGER_RTT_printf(0, "W[0] T=%.d  W[1] T=%.d\r\n", (int)Wells[0].TempGoal,(int)Wells[1].TempGoal);
    while(1){
    	if(State == TEMP_CTRL){
    		for(int i=0; i<2; i++){
    			if(Wells[i].Cycles > 0){
					if(Wells[i].WellState){
						DisableIRQ(LPTMR_INTERRUPT);
						Temp1 = Temp_ReadTemperature(Wells[i].TempAddress);
	                    SEGGER_RTT_printf(0, "%d: %u\n",
	                                      i, Temp_ReadReg(Wells[i].TempAddress));
						if(Temp1 > Wells[i].TempGoal){
							Well_Cool(Wells[i]); // TMP117
						}
						else{
							Well_Heat(Wells[i]);
						}
						EnableIRQ(LPTMR_INTERRUPT);

					}
    			}
    		}
    	}
    }
}

void LPTMR_INTERRUPT_HANDLER(void){
	LPTMR_ClearStatusFlags(LPTMR_BASE, kLPTMR_TimerCompareFlag);
	if(State == IDLE){
		return;
	}
	if(TransmittedBits != -3){
		TransmittedBits = -3;
		Seconds = 0;

		uint32_t CRC_calc = calc_crc32(TransmissionArray, 10);
		uint32_t CRC_Rx = (TransmissionArray[10] << 24) + (TransmissionArray[11] << 16) + (TransmissionArray[12] << 8) + TransmissionArray[13];

		if(CRC_calc != CRC_Rx || CRC_Rx == 0 || CRC_Rx == 0xFF){
			for(int i=0; i<3; i++){
				GPIO_PortClear(LED_GPIO, 1 << LED_PIN);
				for(uint32_t j=0; j<4000; j++){
				}
				GPIO_PortSet(LED_GPIO, 1 << LED_PIN);
				for(uint32_t j=0; j<4000; j++){
				}
			}
			for(int i=0; i<11; i++){
				TransmissionArray[i] = 0;
			}
			return;
		}
		for(int i=0; i<2; i++){
			Wells[i].OnTime = TransmissionArray[i*5];
			Wells[i].Cycles = (TransmissionArray[1 + i*5] << 8) + TransmissionArray[2 + i*5];
			Wells[i].TempGoal = ((TransmissionArray[3 + i*5] << 8) + TransmissionArray[4 + i*5])/10;
		}
		if ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) == kSMC_PowerStateVlpr) {
		    // Request RUN mode
		    SMC->PMCTRL = (SMC->PMCTRL & ~SMC_PMCTRL_RUNM_MASK) | SMC_PMCTRL_RUNM(0b00);

		    // Wait for the transition to RUN to complete
		    while ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) != kSMC_PowerStateRun) {
		        // Wait loop
		    }
		}
		Flash_Clear();
		uint32_t FlashBuffer[3] = {(TransmissionArray[0] << 16) + (TransmissionArray[1] << 8) + (TransmissionArray[2]), (TransmissionArray[5] << 16) + (TransmissionArray[6] << 8) + (TransmissionArray[7]), (TransmissionArray[3] << 24) + (TransmissionArray[4] << 16) + (TransmissionArray[8] << 8) + (TransmissionArray[9])};
		Flash_Write(FlashBuffer,12);
		for(int i=0; i<11; i++){
			TransmissionArray[i] = 0;
		}
		GPIO_PortClear(LED_GPIO, 1 << LED_PIN);
		for(uint32_t i=0; i<4000; i++){
		}
		GPIO_PortSet(LED_GPIO, 1 << LED_PIN);
		Timer_Start();
		State = IDLE;
		return;
	}
	Seconds++;
	if(Seconds >= Wells[0].OnTime && Wells[0].WellState){
		Well_Cool(Wells[0]);
		Temp_Shutdown(Wells[0].TempAddress);
		Wells[0].WellState = false;
		Wells[0].Cycles--;
	}
	if(Seconds >= Wells[1].OnTime && Wells[1].WellState){
		Well_Cool(Wells[1]);
		Temp_Shutdown(Wells[1].TempAddress);
		Wells[1].WellState = false;
		Wells[1].Cycles--;
	}
	if(!Wells[0].WellState && !Wells[1].WellState){
		Timer_Stop();
		State = PREPARE_DOWNLINK;
		if ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) == kSMC_PowerStateVlpr) {
		    // Request RUN mode
		    SMC->PMCTRL = (SMC->PMCTRL & ~SMC_PMCTRL_RUNM_MASK) | SMC_PMCTRL_RUNM(0b00);

		    // Wait for the transition to RUN to complete
		    while ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) != kSMC_PowerStateRun) {
		        // Wait loop
		    }
		}
		Flash_Clear();
		uint32_t FlashBuffer[3] = {(Wells[0].OnTime << 16) + (Wells[0].Cycles), (Wells[1].OnTime << 16) + (Wells[1].Cycles), (((uint16_t)(Wells[0].TempGoal*10)) << 16) + ((uint16_t)(Wells[1].TempGoal*10))};
		Flash_Write(FlashBuffer,12);
		if ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) == kSMC_PowerStateRun) {
		    // Request RUN mode
		    SMC->PMCTRL = (SMC->PMCTRL & ~SMC_PMCTRL_RUNM_MASK) | SMC_PMCTRL_RUNM(2);

		    // Wait for the transition to RUN to complete
		    while ((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) != kSMC_PowerStateVlpr) {
		        // Wait loop
		    }
		}
		Downlink_Setup();
		__NVIC_SetPriority(DOWNLINK_INTERRUPT,0);
		GPIO_PortClear(LED_GPIO, 1 << LED_PIN);
		for(uint32_t i=0; i<1600; i++){
		}
		GPIO_PortSet(LED_GPIO, 1 << LED_PIN);
	}
}

void DOWNLINK_INTERRUPT_HANDLER(void){
	if(State == STARTUP){
		return;
	}

	CMP_ClearStatusFlags(CMP0, kCMP_OutputFallingEventFlag);

	if(SkipBit){
		SkipBit = !SkipBit;
		return;
	}
	SkipBit = !SkipBit;

//	GPIO_PortToggle(LED_GPIO, 1 << LED_PIN);

	switch(TransmittedBits){
		case -3:
			Timer_Start();
			Well_Cool(Wells[0]);
			Well_Cool(Wells[1]);
			State = DOWNLINK;
			break;
		case -2:
			Time0 = LPTMR_GetCurrentTimerCount(LPTMR_BASE);
			Timer_Stop();
			Timer_Start();
			break;
		case -1:
			Time1 = LPTMR_GetCurrentTimerCount(LPTMR_BASE);
			BitCutoff = (Time0+Time1)/2;
			Timer_Stop();
			Timer_Start();
			break;
		default:
			Duration = LPTMR_GetCurrentTimerCount(LPTMR_BASE);
			TransmissionArray[TransmittedBits/8] |= (Duration > BitCutoff) << (7-(TransmittedBits%8));
			Timer_Stop();
			Timer_Start();
			break;
	}
	TransmittedBits++;
}
