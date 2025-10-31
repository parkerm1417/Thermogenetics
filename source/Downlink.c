#include "Downlink.h"

cmp_config_t DownlinkConfig;

void Downlink_Setup(){
	EnableIRQ(DOWNLINK_INTERRUPT);
	CMP_GetDefaultConfig(&DownlinkConfig);
	DownlinkConfig.hysteresisMode = kCMP_HysteresisLevel3;
	CMP_Init(CMP0, &DownlinkConfig);

	CMP_SetInputChannels(CMP0, 0, 1);

	cmp_filter_config_t mCmpFilter;
	mCmpFilter.filterCount = 7;
	mCmpFilter.filterPeriod = 10;
	CMP_SetFilterConfig(CMP0, &mCmpFilter);

	CMP_ClearStatusFlags(CMP0, kCMP_OutputFallingEventFlag);
	CMP_EnableInterrupts(CMP0, kCMP_OutputFallingInterruptEnable);
	CMP_DisableInterrupts(CMP0, kCMP_OutputRisingInterruptEnable);
}

