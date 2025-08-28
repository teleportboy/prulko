#include "../adc.h"

void setupADC()
{
    CLOCK_SetRootDivider(kCLOCK_RootEcspi2, 4U, 10U); //20mhz
    CLOCK_SetRootMux(kCLOCK_RootEcspi2, kCLOCK_EcspiRootmuxSysPll1);   

    ecspi_master_config_t masterConfig;
    ECSPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.channelConfig.phase    = kECSPI_ClockPhaseFirstEdge;
    masterConfig.channelConfig.polarity = kECSPI_PolarityActiveLow;
    
    masterConfig.channelConfig.chipSlectActiveState  = kECSPI_ChipSelectActiveStateLow;
    masterConfig.channelConfig.clockInactiveState    = kECSPI_ClockInactiveStateHigh;
    masterConfig.channelConfig.dataLineInactiveState = kECSPI_DataLineInactiveStateLow;

    masterConfig.burstLength = 16;
   
    masterConfig.txFifoThreshold = 0;
    masterConfig.rxFifoThreshold = 0;

    masterConfig.chipSelectDelay = 0;
    
    gpio_pin_config_t pdrstConfig = { kGPIO_DigitalOutput, 0, kGPIO_NoIntmode };
    GPIO_PinInit(GPIO4, 30, &pdrstConfig);
    GPIO_PinWrite(GPIO4, 30, 1);

    ECSPI_MasterInit(ECSPI2, &masterConfig, ECSPI_MASTER_CLK_FREQ);
    ECSPI2->CONFIGREG |= ECSPI_CONFIGREG_SS_CTL(1); //DONT TOUCH!
}

uint32_t createADCReadCommand(uint32_t channel) 
{
    uint32_t commandReadADC = 1 << 15;
    commandReadADC |= 1 << (13 - channel);
    return (commandReadADC << 16) | commandReadADC;
}

uint32_t readADCbyChannel(uint32_t channel)
{
    ecspi_transfer_t masterXfer;

    uint32_t command = createADCReadCommand(channel);
    uint32_t rxData = 0;

    masterXfer.txData   = &command;
    masterXfer.rxData   = &rxData;
    masterXfer.dataSize = 1;
    masterXfer.channel  = kECSPI_Channel0;

    ECSPI_MasterTransferBlocking(ECSPI2, &masterXfer);

    return rxData;
}

static const uint8_t adcChannelMap[CHANNELS_COUNT] = { 6, 7, 5, 0, 1, 2, 3, 4 };
int fillAdcIfNew(uint32_t *adcChannelValues) 
{
    static uint32_t nextChannelToRead = 0;
    
    uint32_t adcChannelData = readADCbyChannel(nextChannelToRead);
    uint32_t channelId = adcChannelData >> 12;
    if(channelId >= CHANNELS_COUNT) {
        return 0;
    }

    uint8_t position = adcChannelMap[channelId];
    adcChannelValues[position] = adcChannelData & 0x00000FFF;

    if(++nextChannelToRead == CHANNELS_COUNT) {
        nextChannelToRead = 0;
        return 1;
    }

    return 0;
}
