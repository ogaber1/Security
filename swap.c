#include "swap.h"

uint64_t swap(uint64_t block){
    
    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFFU);

    return ((uint64_t)right << 32) | (uint64_t)left;
}
