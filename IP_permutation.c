//
// Created by hussi on 10/25/2025.
//

#include "IP_permutation.h"
static inline uint64_t initial_permutation(uint64_t block)
{
    uint32_t left  = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFFU);
    uint32_t u;

    /* step 1 */
    u = ((left >> 4) ^ right) & 0x0F0F0F0FU;
    right ^= u;
    left  ^= (u << 4);

    /* step 2 */
    u = ((left >> 16) ^ right) & 0x0000FFFFU;
    right ^= u;
    left  ^= (u << 16);

    /* step 3 */
    u = ((right >> 2) ^ left) & 0x33333333U;
    left  ^= u;
    right ^= (u << 2);

    /* step 4 */
    u = ((right >> 8) ^ left) & 0x00FF00FFU;
    left  ^= u;
    right ^= (u << 8);

    /* step 5 */
    u = ((left >> 1) ^ right) & 0x55555555U;
    right ^= u;
    left  ^= (u << 1);

    return ((uint64_t)left << 32) | (uint64_t)right;
}