#ifndef DOWNLINK_H_
#define DOWNLINK_H_

#include "fsl_cmp.h"

#define DOWNLINK_INTERRUPT CMP0_IRQn
#define DOWNLINK_INTERRUPT_HANDLER CMP0_IRQHandler

extern cmp_config_t DownlinkConfig;

void Downlink_Setup(void);

#endif /* DOWNLINK_H_ */
