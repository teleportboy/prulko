#ifndef DIGITALS_KOBUS_H
#define DIGITALS_KOBUS_H

#include "stdint-gcc.h"

void setupDigitalInputs();
uint32_t readPort(uint32_t portId);
uint8_t getDigitalParams();

#endif