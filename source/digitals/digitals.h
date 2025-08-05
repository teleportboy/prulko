#ifndef DIGITALS_H
#define DIGITALS_H

#include "stdint-gcc.h"

void setupDigitalInputs();
uint32_t readPort(uint32_t portId);
uint8_t getDigitalParams();

#endif