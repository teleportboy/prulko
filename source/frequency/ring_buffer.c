#include "ring_buffer.h"


uint32_t ringIndexAhead(uint32_t head, uint32_t maxlen, uint32_t step) {
    return (head + step) % maxlen;
}

uint32_t ringIndexBehind(uint32_t head, uint32_t maxlen, uint32_t step) {
    return (head - step + maxlen) % maxlen;
}


