#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "board.h"

void BOARD_InitBootPins(void);
void pinctrlADC(void);
void pinctrlDigitals(void);

#endif