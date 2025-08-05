#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define WAVE_RING_SIZE        255
#define CYCLES_RING_SIZE      15
#define WAVES_PER_1000MS_SIZE 10
#define WAVES_PER_2000MS_SIZE 20
#define WAVES_PER_3000MS_SIZE 30
#define WAVES_PER_5000MS_SIZE 50



// Данные одного узла
typedef struct TicksData {
    uint32_t tickHi;
    uint32_t tickLo;
    uint32_t waveTicks;    
    uint32_t wavesCountAtInterval;
} TicksData;

typedef struct ArrRingBuffer {
    TicksData* data;

    const uint32_t maxlen;

    uint32_t completeCyclesCount;

    uint32_t head;
    uint32_t tail;
} RingBuffer;

#define INIT_RING_BUFFER_ARRAY(NAME, BUF_CNT, MAXLEN)             \
static TicksData NAME##_nodes[(BUF_CNT)][(MAXLEN)];               \
static RingBuffer NAME[(BUF_CNT)] = {                             \
    [0 ... ((BUF_CNT) - 1)] = {                                   \
        .data = NULL,                                             \
        .maxlen   = (MAXLEN),                                     \
        .completeCyclesCount = 0,                                 \
        .head = 0,                                                \
        .tail = 0                                                 \
    }                                                             \
};                                                                \
void NAME##InitNodes(RingBufferSet* ringSet) {                    \
    for (int i = 0; i < (BUF_CNT); i++) {                         \
        NAME[i].data = &NAME##_nodes[i][0];                       \
    }                                                             \
    ringSet->NAME##Ring = NAME;                                   \
}                                                                 \



uint32_t ringIndexAhead(uint32_t head, uint32_t maxlen, uint32_t step);
uint32_t ringIndexBehind(uint32_t head, uint32_t maxlen, uint32_t step);

#endif // RING_BUFFER_H