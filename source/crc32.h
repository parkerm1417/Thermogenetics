#ifndef CRC32_H_
#define CRC32_H_

#include "stdint.h"

#define CRC32_POLYNOMIAL 0xEDB88320UL

int32_t calc_crc32(const void *data, uint8_t length);

#endif /* CRC32_H_ */
