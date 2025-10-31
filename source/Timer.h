#ifndef HEADER_AND_C_FILES_TIMER_H_
#define HEADER_AND_C_FILES_TIMER_H_

#include "fsl_lptmr.h"
#include "clock_config.h"
#include "fsl_tpm.h"

#define LPTMR_BASE LPTMR0 //Timer base in the MCU
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk) //Timer frequency
#define LPTMR_MSEC_COUNT 60000U //Maximum value for timer in milliseconds
#define LPTMR_INTERRUPT LPTMR0_IRQn
#define LPTMR_INTERRUPT_HANDLER LPTMR0_IRQHandler

#define TPM_BASE TPM0
#define TPM_INTERRUPT TPM0_IRQn
#define TPM_INTERRUPT_HANDLER TPM0_IRQHandler

extern lptmr_config_t lptmrConfig; //Configuration for the timer
extern tpm_config_t tpmConfig;

void Timer_SetupAll(void); //Initialize and setup the timer

void CommsTimer_Start(void);

void CommsTimer_Stop(void);

void Timer_Start(void); //Start the timer

void Timer_Stop(void); //Stop the timer

void Timer_EnableInterrupt(void); //Enables timer interrupt

void Timer_DisableInterrupt(void); //Disables timer interrupt
#endif /* HEADER_AND_C_FILES_TIMER_H_ */
