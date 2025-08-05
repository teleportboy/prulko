#ifndef CYCLE_TIMER_H
#define CYCLE_TIMER_H

#include "stdint-gcc.h"
#include "../../prulko/hardfrequencylevel.h"

void start200MHzTimer();
void initGPT2(void);
void startLowFreqTimer(FrequenceExchange *mem);

unsigned int pruCycle31bit();
unsigned int getLowFreqCount();
void updateFrequencyIfNeeded(FrequenceExchange *mem);


#endif