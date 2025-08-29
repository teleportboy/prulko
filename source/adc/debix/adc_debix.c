#include "../adc.h"
#include "adc_debix_hw.h"

#include "../../../prulko/prutypes.h"

#define ADS7128_I2C            I2C2
#define ADS7128_I2C_ADDRESS    0x10   // 7-bit адрес (ADDR=GND)
#define ADS7128_REG_CHAN_SEL   0x11   // регистр CHANNEL_SEL
#define ADS7128_REG_RECENT_LSB 0xA0   // LSB регистр для канала 0

#define pruSharedOCRAMAddresKobusX         ((PruSharedData *) 0x00900000   )

void setupADC()
{
    // SDK_DelayAtLeastUs(5U, SystemCoreClock); //wait for power on(на всякий случай)
    PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    mem->frequence.tickUsec = 1000;
    CLOCK_SetRootMux(kCLOCK_I2c2, kCLOCK_I2cRootmuxOsc24M); //тут падает
    mem->frequence.tickUsec = 2000;
    CLOCK_SetRootDivider(kCLOCK_I2c2, 1U, 1U);
    mem->frequence.tickUsec = 3000;
    CLOCK_EnableClock(kCLOCK_I2c2);

    i2c_master_config_t i2cConfig;
    //mem->frequence.tickUsec = 4000;
    I2C_MasterGetDefaultConfig(&i2cConfig);
    //mem->frequence.tickUsec = 5000;
    i2cConfig.baudRate_Bps = 100000U;
    //mem->frequence.tickUsec = 6000;
    I2C_MasterInit(ADS7128_I2C, &i2cConfig, CLOCK_GetClockRootFreq(kCLOCK_I2c2ClkRoot));
    //mem->frequence.tickUsec = 7000;
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
    PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    //mem->frequence.tickUsec += 1;
    // 1) Выбрать канал (CHANNEL_SEL.MANUAL_CHID = ch)
    ads7128_write8(0x11u, (uint8_t)(ch & 0x0Fu));  // CHANNEL_SEL = 0x11 :contentReference[oaicite:7]{index=7}

    // 2) Conversion start + чтение кадра Frame A (2 байта, без под-адреса)
    uint8_t b[2] = {0};
    i2c_master_transfer_t t = {0};
    t.slaveAddress   = ADS7128_I2C_ADDRESS;
    t.direction      = kI2C_Read;
    t.subaddressSize = 0;                // важный момент: без под-адреса
    t.data           = b;
    t.dataSize       = 2;                // Frame A = 2 байта :contentReference[oaicite:8]{index=8}
    t.flags          = kI2C_TransferDefaultFlag;
    I2C_MasterTransferBlocking(ADS7128_I2C, &t); // устройство может растянуть SCL до готовности результата :contentReference[oaicite:9]{index=9}

    // 3) Склейка 12 бит (D11..D0)
    uint16_t code12 = ((uint16_t)b[0] << 4) | (b[1] >> 4);
    return code12; // 0..0x0FFF
}

int fillAdcIfNew(uint32_t *adcChannelValues)
{
    static const uint8_t adcChannelMap[CHANNELS_COUNT] = { 6, 7, 5, 0, 1, 2, 3, 4 };
    static uint32_t currentChannelToRead = 0;

    adcChannelValues[currentChannelToRead] = readADCbyChannel(adcChannelMap[currentChannelToRead]);
    currentChannelToRead++;
    
    if (currentChannelToRead >= CHANNELS_COUNT) {
        currentChannelToRead = 0;
        return 1; // all channels read
    }
    return 0; // not all channels read yet
}

status_t ads7128_write8(uint8_t reg, uint8_t val) 
{
    PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    mem->frequence.tickUsec = 500;
    i2c_master_transfer_t t = {0};
    t.slaveAddress   = ADS7128_I2C_ADDRESS;
    t.direction      = kI2C_Write;
    t.subaddress     = ((uint16_t)ADS7128_OP_WR_REG << 8) | reg; // отправится 0x08, затем reg
    t.subaddressSize = 2;
    t.data           = &val;
    t.dataSize       = 1;
    t.flags          = kI2C_TransferDefaultFlag;
    status_t res = I2C_MasterTransferBlocking(ADS7128_I2C, &t);
    mem->frequence.tickUsec++;
    
    return res;
}