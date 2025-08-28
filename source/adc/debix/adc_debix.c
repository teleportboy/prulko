#include "../adc.h"

#define ADS7128_I2C            I2C2
#define ADS7128_I2C_ADDRESS    0x10   // 7-bit адрес (ADDR=GND)
#define ADS7128_REG_CHAN_SEL   0x11   // регистр CHANNEL_SEL
#define ADS7128_REG_RECENT_LSB 0xA0   // LSB регистр для канала 0

void setupADC()
{
    SDK_DelayAtLeastUs(5000U, SystemCoreClock); //wait for power on(на всякий случай)
    CLOCK_SetRootMux(kCLOCK_I2c2, kCLOCK_I2cRootmuxOsc24M);
    CLOCK_SetRootDivider(kCLOCK_I2c2, 1U, 1U);
    CLOCK_EnableClock(kCLOCK_I2c2);

    i2c_master_config_t i2cConfig;
    I2C_MasterGetDefaultConfig(&i2cConfig);
    i2cConfig.baudRate_Bps = 100000U;
    I2C_MasterInit(ADS7128_I2C, &i2cConfig, CLOCK_GetClockRootFreq(kCLOCK_I2c2ClkRoot));
}

uint32_t createADCReadCommand(uint32_t channel) 
{
    if (channel >= CHANNELS_COUNT) {
        channel = 0;
    }

    return (uint16_t)channel;
}

uint32_t readADCbyChannel(uint32_t ch)
{
    uint8_t channel = (uint8_t)ch;  // извлекаем номер канала
    uint8_t txData = channel & 0x0F; // канал 0..7
    uint8_t rxBuf[2] = {0};
    i2c_master_transfer_t transfer;

    // 1) Запись номера канала в регистр CHANNEL_SEL (адрес 0x11) 
    transfer.slaveAddress   = ADS7128_I2C_ADDRESS;
    transfer.direction      = kI2C_Write;
    transfer.subaddress     = ADS7128_REG_CHAN_SEL;
    transfer.subaddressSize = 1;
    transfer.data           = &txData;
    transfer.dataSize       = 1;
    transfer.flags          = kI2C_TransferDefaultFlag;
    I2C_MasterTransferBlocking(ADS7128_I2C, &transfer);

    // Теперь началась конверсия выбранного канала (устройство держит SCL низко до окончания).

    // 2) Чтение 2 байт результата. Адрес LSB-регистра зависит от канала:
    uint8_t regLSB = ADS7128_REG_RECENT_LSB + (uint8_t)(channel * 2u);
    transfer.direction      = kI2C_Read;
    transfer.subaddress     = regLSB;
    transfer.subaddressSize = 1;
    transfer.data           = rxBuf;   // прочитаем 2 байта подряд: LSB, MSB
    transfer.dataSize       = 2;
    transfer.flags          = kI2C_TransferDefaultFlag;
    I2C_MasterTransferBlocking(I2C2, &transfer);

    // 3) Объединяем два байта в 12-битный результат.
    // Согласно даташиту, первый байт содержит младшие 8 бит, второй — старшие 8 бит результата
    uint16_t value = ((uint16_t)rxBuf[1] << 8) | rxBuf[0];
    // Ограничиваем 12 битами (хотя старшие 4 бита должны быть нулевыми).
    value &= 0x0FFFu;
    return value;
}

int fillAdcIfNew(uint32_t *adcChannelValues)
{
    static const uint8_t adcChannelMap[CHANNELS_COUNT] = { 6, 7, 5, 0, 1, 2, 3, 4 };
    for (uint32_t i = 0; i < CHANNELS_COUNT; i++) {
        uint8_t ch = adcChannelMap[i];
        //uint16_t command = createADCReadCommand(ch);
        uint32_t result = readADCbyChannel(ch);
        result = 111 + result;
        adcChannelValues[i] = result;
    }
    return 1;
}