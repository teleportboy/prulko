#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

void BOARD_InitBootPins(void)
{
    // pinctrlADC();
    // pinctrlDigitals();
}

void pinctrlADC(void) {
    // IOMUXC_SetPinMux(IOMUXC_I2C3_SCL_ECSPI2_SCLK, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_I2C3_SCL_ECSPI2_SCLK, 
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    // IOMUXC_SetPinMux(IOMUXC_I2C3_SDA_ECSPI2_MOSI, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_I2C3_SDA_ECSPI2_MOSI, 
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    
    
    // IOMUXC_SetPinMux(IOMUXC_I2C4_SCL_ECSPI2_MISO, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_I2C4_SCL_ECSPI2_MISO, 
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    // IOMUXC_SetPinMux(IOMUXC_ECSPI2_SS0_ECSPI2_SS0, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_ECSPI2_SS0_ECSPI2_SS0, 
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    // //pd/rst    
    // IOMUXC_SetPinMux(IOMUXC_SAI3_RXD_GPIO4_IO30, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SAI3_RXD_GPIO4_IO30, 
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
}

void pinctrlDigitals(void) 
{
    // IOMUXC_SetPinMux(IOMUXC_SAI1_MCLK_GPIO4_IO20, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SAI1_MCLK_GPIO4_IO20,
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    // IOMUXC_SetPinMux(IOMUXC_SAI1_TXD0_GPIO4_IO12, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SAI1_TXD0_GPIO4_IO12,
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    // IOMUXC_SetPinMux(IOMUXC_SAI1_TXD7_GPIO4_IO19, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SAI1_TXD7_GPIO4_IO19,
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    // IOMUXC_SetPinMux(IOMUXC_SAI2_RXFS_GPIO4_IO21, 0U);
    // IOMUXC_SetPinConfig(IOMUXC_SAI2_RXFS_GPIO4_IO21,
    //                     IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
    //                     IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
}