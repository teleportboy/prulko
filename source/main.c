#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_ecspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_gpt.h"
#include "adc/ads8028.h"
#include "digitals/digitals.h"
#include "timer/cycle_timer.h"
#include "frequency/ring_buffer.h"

#include "../../kobus/kobus9/firm/pru/prulko/prutypes.h"

#include "../../kobus/kobus9/firm/pru/prulko/prutypes.h"
#include "../../kobus/kobus9/firm/pru/prulko/harddepthlevel.h"
#include "../../kobus/kobus9/firm/pru/prulko/hardadclevel.h"
#include "../../kobus/kobus9/firm/pru/prulko/hardrpmlevel.h"
#include "../../kobus/kobus9/firm/pru/prulko/kobus_pru.h"

// #include "../../kobus/kobus9/firm/pru/prulko/hardfrequencylevel.h"

#include "../../kobus/kobus9/firm/pru/prulko/hardfrequencylevel.h"

#define pruSharedDDRAddresKobusX           ((PruSharedData *) 0x80000000   )
#define pruSharedOCRAMAddresKobusX         ((PruSharedData *) 0x00900000   )

INIT_RING_BUFFER_ARRAY(wave,             8, WAVE_RING_SIZE);
INIT_RING_BUFFER_ARRAY(cycles,           8, CYCLES_RING_SIZE);
INIT_RING_BUFFER_ARRAY(wavesPerInterval, 8, WAVES_PER_5000MS_SIZE);

void doPruStep(RingBufferSet *ringSet)
{
    PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    doDepthStep(&mem->depth, &mem->debugDepth);
    doDigitalStep(&mem->digital);
    doCalculationsStep(&mem->digital);
    doRpmStep(&mem->rpm);
    doFrequencyStep(&mem->frequence, ringSet);
}

void GPT2_IRQHandler(void)
{
    // PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    // if (GPT_GetStatusFlags(GPT2, kGPT_OutputCompare1Flag)) {
    //     GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
    //     doAdcStep(&mem->adc);
    // }
}

int main()
{
    BOARD_BootClockRUN();
    BOARD_InitMemory();
    BOARD_RdcInit();
    unsigned int counter = 0;
    while (1) {
        counter += 1;
        /* code */
    }
    return 0;
    
    // PruSharedData *mem = pruSharedOCRAMAddresKobusX;
    // RingBufferSet ringSet;

    // memset(&mem->frequence, 0, sizeof(FrequenceExchange));

    
    // BOARD_RdcInit();

    // BOARD_InitBootPins();
    

    // //initGPT2();
    // start200MHzTimer();
    // startLowFreqTimer(&mem->frequence);

    // //setupECSPI2ForADS8028();
    // setupDigitalInputs();

    // waveInitNodes(&ringSet);    
    // cyclesInitNodes(&ringSet);
    // wavesPerIntervalInitNodes(&ringSet);

    // while(1) {
    //     doPruStep(&ringSet);
    // }

    // return 0;
}
