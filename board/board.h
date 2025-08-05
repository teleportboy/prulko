#ifndef _BOARD_H_
#define _BOARD_H_
#include "clock_config.h"
#include "fsl_clock.h"
#include "fsl_audiomix.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME        "MIMX8MP-EVK"
#define MANUFACTURER_NAME "NXP"
#define BOARD_DOMAIN_ID   (1U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
void BOARD_InitDebugConsole(void);
void BOARD_InitMemory(void);
void BOARD_RdcInit(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
