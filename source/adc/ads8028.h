#ifndef ADS8028_H
#define ADS8028_H

#include "stdint-gcc.h"
#include "fsl_ecspi.h"
#include "fsl_gpio.h"

#define TRANSFER_BAUDRATE 5000000U

#define ECSPI_MASTER_CLK_FREQ                                                                 \
    (CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootEcspi2)) / \
    (CLOCK_GetRootPostDivider(kCLOCK_RootEcspi2)))
#define CHANNELS_COUNT 8

void setupECSPI2ForADS8028();
uint32_t createADCReadCommand(uint32_t channel);
uint32_t readADCbyChannel(uint32_t channel);
int fillAdcIfNew(uint32_t *adcChannelValues);


#endif