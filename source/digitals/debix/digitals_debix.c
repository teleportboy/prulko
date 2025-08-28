#include "fsl_gpio.h"
#include "../digitals.h"

void setupDigitalInputs() 
{
    gpio_pin_config_t dig = { kGPIO_DigitalInput, 0, kGPIO_NoIntmode };
    GPIO_PinInit(GPIO1, 5, &dig);

    gpio_pin_config_t rot = { kGPIO_DigitalInput, 0, kGPIO_NoIntmode };
    GPIO_PinInit(GPIO1, 6, &rot);

    gpio_pin_config_t depa = { kGPIO_DigitalInput, 0, kGPIO_NoIntmode };
    GPIO_PinInit(GPIO1, 7, &depa);

    gpio_pin_config_t depb = { kGPIO_DigitalInput, 0, kGPIO_NoIntmode };
    GPIO_PinInit(GPIO1, 8, &depb);
}

static const GPIO_Type* gpioMap[8] = { GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO1, GPIO2, GPIO3 };
uint32_t readPort(uint32_t portId)
{
    return gpioMap[portId & 7]->DR;
}

uint8_t getDigitalParams()
{
    //DEPTHA DEPTHB DIG ROT POWER
    uint32_t g1 = GPIO1->DR;
    uint32_t gp = SNVS->HPSR;
    return ((g1 >> 7) & 0x03) | ((g1 >> 3) & 0x04) | (( g1 >> 3 ) & 0x08) | ((gp >> 2) & 0x10);
}

