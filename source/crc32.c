#include "crc32.h"

int32_t calc_crc32(const void *data, uint8_t length) {
	const uint8_t *bytes = (const uint8_t *)data;
    int32_t crc = 0xFFFFFFFF; // Initial CRC value

    for (uint8_t i = 0; i < length; i++) {
        crc ^= bytes[i]; // XOR current byte with CRC

        for (uint8_t j = 0; j < 8; ++j) { // Process 8 bits of the current byte
            if (crc & 1) { // If the LSB is 1
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL; // Shift right and XOR with polynomial
            } else {
                crc >>= 1; // Shift right
            }
        }
    }

    return ~crc; // Final XOR with 0xFFFFFFFF
}
