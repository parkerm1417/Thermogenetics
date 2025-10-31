#include "Timer.h"

lptmr_config_t lptmrConfig;
tpm_config_t tpmConfig;

void Timer_SetupAll(void){
	LPTMR_GetDefaultConfig(&lptmrConfig);
	LPTMR_Init(LPTMR_BASE, &lptmrConfig);
	LPTMR_SetTimerPeriod(LPTMR_BASE, MSEC_TO_COUNT(1000, LPTMR_SOURCE_CLOCK)); //Set timer period based on count in header file
    __NVIC_SetPriority(LPTMR_INTERRUPT,1);
	Timer_EnableInterrupt();
	LPTMR_ClearStatusFlags(LPTMR_BASE, kLPTMR_TimerCompareFlag);
	EnableIRQ(LPTMR_INTERRUPT);
	LPTMR_ClearStatusFlags(LPTMR_BASE, kLPTMR_TimerCompareFlag);

//	CLOCK_SetTpmClock(3U);
//	TPM_GetDefaultConfig(&tpmConfig);
//	tpmConfig.prescale = kTPM_Prescale_Divide_32;
//	tpmConfig.enableStopOnOverflow = true;
//	TPM_Init(TPM_BASE, &tpmConfig);
//	TPM_SetTimerPeriod(TPM_BASE, 0xFFFF);
//	__NVIC_SetPriority(TPM_INTERRUPT,2);
//	TPM_EnableInterrupts(TPM_BASE, kTPM_TimeOverflowInterruptEnable);
//	TPM_ClearStatusFlags(TPM_BASE, kTPM_TimeOverflowFlag);
//	EnableIRQ(TPM_INTERRUPT);
//	TPM_ClearStatusFlags(TPM_BASE, kTPM_TimeOverflowFlag);
}

void CommsTimer_Start(void){
	TPM_StartTimer(TPM_BASE, kTPM_SystemClock);
}

void CommsTimer_Stop(void){
	TPM_StopTimer(TPM_BASE);
}

void Timer_Start(void){
	LPTMR_StartTimer(LPTMR_BASE);
}

void Timer_Stop(void){
	LPTMR_StopTimer(LPTMR_BASE);
}

void Timer_EnableInterrupt(void){
	LPTMR_EnableInterrupts(LPTMR_BASE, kLPTMR_TimerInterruptEnable);
}

void Timer_DisableInterrupt(void){
	LPTMR_DisableInterrupts(LPTMR_BASE, kLPTMR_TimerInterruptEnable);
}
