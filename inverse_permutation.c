#include "inverse_permutation.h"

uint64_t inverse_permutation(uint64_t block){
    
    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFFU);
    uint32_t u;

    /* Reverse of step 5 (from initial_permutation) */
    u = ((left >> 1) ^ right) & 0x55555555U;
    right ^= u;
    left ^= (u << 1);

    /* Reverse of step 4 */
    u = ((right >> 8) ^ left) & 0x00FF00FFU;
    left ^= u;
    right ^= (u << 8);

    /* Reverse of step 3 */
    u = ((right >> 2) ^ left) & 0x33333333U;
    left ^= u;
    right ^= (u << 2);

    /* Reverse of step 2 */
    u = ((left >> 16) ^ right) & 0x0000FFFFU;
    right ^= u;
    left ^= (u << 16);

    /* Reverse of step 1 */
    u = ((left >> 4) ^ right) & 0x0F0F0F0FU;
    right ^= u;
    left ^= (u << 4);

    return ((uint64_t)left << 32) | (uint64_t)right;
}