/*********************************************************************
* Minimal SEGGER RTT configuration for small MCUs (e.g., MKL02Z32)
*********************************************************************/

#ifndef SEGGER_RTT_CONF_H
#define SEGGER_RTT_CONF_H

#include <stdint.h>
#include "cmsis_gcc.h"              /* Core Peripheral Access Layer */
/*********************************************************************
* Buffer configuration
*********************************************************************/

#define SEGGER_RTT_MAX_NUM_UP_BUFFERS      (2)
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS    (2)

#define SEGGER_RTT_BUFFER_SIZE_UP          (512)   // 0→PC
#define SEGGER_RTT_BUFFER_SIZE_DOWN        (32)    // PC→0

/*********************************************************************
* RTT behavior flags
*********************************************************************/
#define SEGGER_RTT_PRINTF_BUFFER_SIZE      (64)
#define SEGGER_RTT_MODE_DEFAULT            SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL

/*********************************************************************
* Target-specific configuration
*********************************************************************/
#define SEGGER_RTT_CPU_CACHE_LINE_SIZE     (0)
#define SEGGER_RTT_LOCK()                  __disable_irq()
#define SEGGER_RTT_UNLOCK()                __enable_irq()

#endif
