#include "../adc.h"

#define ADS7128_OP_RD_REG   0x10u   // single register read
#define ADS7128_OP_WR_REG   0x08u   // single register write
#define ADS7128_OP_RD_BLOCK 0x30u   // block read

status_t ads7128_write8(uint8_t reg, uint8_t val);