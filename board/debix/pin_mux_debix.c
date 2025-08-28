#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

void BOARD_InitBootPins(void)
{
    pinctrlADC();
    pinctrlDigitals();
}

void pinctrlADC(void) {
    // I2C2_SCL
    IOMUXC_SetPinMux(IOMUXC_I2C2_SCL_I2C2_SCL, 0U);
    IOMUXC_SetPinConfig(IOMUXC_I2C2_SCL_I2C2_SCL,
          IOMUXC_SW_PAD_CTL_PAD_ODE_MASK          // open-drain
        | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK          // hysteresis
        | IOMUXC_SW_PAD_CTL_PAD_DSE(2)            // drive strength
        // подтяжкa
        //| IOMUXC_SW_PAD_CTL_PAD_PUE_MASK        // pull enable
        //| IOMUXC_SW_PAD_CTL_PAD_PUS(3)          // pull-up
    );

    // I2C2_SDA
    IOMUXC_SetPinMux(IOMUXC_I2C2_SDA_I2C2_SDA, 0U);
    IOMUXC_SetPinConfig(IOMUXC_I2C2_SDA_I2C2_SDA,
          IOMUXC_SW_PAD_CTL_PAD_ODE_MASK
        | IOMUXC_SW_PAD_CTL_PAD_HYS_MASK
        | IOMUXC_SW_PAD_CTL_PAD_DSE(2)
        //| IOMUXC_SW_PAD_CTL_PAD_PUE_MASK
        //| IOMUXC_SW_PAD_CTL_PAD_PUS(3)
    );
}

void pinctrlDigitals(void) 
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO05_GPIO1_IO05, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO05_GPIO1_IO05,
                        IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO06_GPIO1_IO06, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO06_GPIO1_IO06,
                        IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO07_GPIO1_IO07, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO07_GPIO1_IO07,
                        IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08,
                        IOMUXC_SW_PAD_CTL_PAD_DSE(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
}