#include "cycle_timer.h"
#include "fsl_gpt.h"
#include "../../prulko/hardfrequencylevel.h"

//CLOCK = 800MHz
//+SYSTEM_PLL1_DIV2  400MHz
//-SYSTEM_PLL1_DIV3  266MHz
//-SYSTEM_PLL1_DIV4  200MHz
//-SYSTEM_PLL1_DIV5  160MHz
//+SYSTEM_PLL1_DIV10 80MHz
//+SYSTEM_PLL1_DIV20 40MHz
//+SYSTEM_PLL2_DIV10 100MHz
//SYSTEM_PLL2_CLK 1000MHz
//+REF24 24MHz
void start200MHzTimer()
{
    CLOCK_SetRootMux(kCLOCK_RootGpt1, kCLOCK_GptRootmuxSysPll1Div2); //400MHz
    CLOCK_SetRootDivider(kCLOCK_RootGpt1, 2U, 1U); //pre = 2 and post div = 1 -> 200MHz

    gpt_config_t gptConfig;

    GPT_GetDefaultConfig(&gptConfig);
    gptConfig.clockSource = kGPT_ClockSource_HighFreq;
    gptConfig.enableFreeRun = true;

    GPT_Init(GPT1, &gptConfig);

    GPT_StartTimer(GPT1);
}

void initGPT2(void)
{
    CLOCK_SetRootMux(kCLOCK_RootGpt2, kCLOCK_GptRootmuxSysPll1Div2); 
    CLOCK_SetRootDivider(kCLOCK_RootGpt2, 2U, 1U); //200mhz                  

    gpt_config_t gptConfig;
    GPT_GetDefaultConfig(&gptConfig);
    
    gptConfig.enableMode = true;                  
    gptConfig.clockSource = kGPT_ClockSource_HighFreq;
    gptConfig.divider = 1;                           

    GPT_Init(GPT2, &gptConfig);
    GPT_SetOutputCompareValue(GPT2, kGPT_OutputCompare_Channel1, 100000); 

    GPT_EnableInterrupts(GPT2, kGPT_OutputCompare1InterruptEnable);
    EnableIRQ(GPT2_IRQn);

    GPT_StartTimer(GPT2);
}

void startLowFreqTimer(FrequenceExchange *mem)
{
    CLOCK_SetRootMux(kCLOCK_RootGpt3, kCLOCK_GptRootmuxSysPll1Div20); //40MHz
    CLOCK_SetRootDivider(kCLOCK_RootGpt3, 8U, 5U); //pre = 5 and post div = 8 -> 1MHz

    gpt_config_t gptConfig;

    GPT_GetDefaultConfig(&gptConfig);
    gptConfig.clockSource = kGPT_ClockSource_HighFreq;
    gptConfig.enableFreeRun = true;
    if (mem->requestTickUsec == 0) {
        mem->tickUsec = 1000; //default 1ms
    }
    gptConfig.divider = mem->tickUsec;

    GPT_Init(GPT3, &gptConfig);

    GPT_StartTimer(GPT3);
}

unsigned int getLowFreqCount() 
{
    return GPT_GetCurrentTimerCount(GPT3);
}

unsigned int pruCycle31bit()
{
    return GPT_GetCurrentTimerCount(GPT1);
}

void updateFrequencyIfNeeded(FrequenceExchange *mem)
{
    if (mem->requestTickUsec != 0 && mem->requestTickUsec != mem->tickUsec) {
        GPT_StopTimer(GPT3);

        mem->tickUsec = mem->requestTickUsec;
        mem->requestTickUsec = 0;

        uint32_t divider = mem->tickUsec;

        gpt_config_t gptConfig;
        GPT_GetDefaultConfig(&gptConfig);
        gptConfig.clockSource = kGPT_ClockSource_HighFreq;
        gptConfig.enableFreeRun = true;
        gptConfig.divider = divider;

        GPT_Init(GPT3, &gptConfig);
        GPT_StartTimer(GPT3);
    }
}

