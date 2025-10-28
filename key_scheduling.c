#include "key_scheduling.h"
#include <stdio.h>
#include <stdint.h>


// Permuted choice 1 (PC-1) table
     const int PC1[] = {
        57,49,41,33,25,17,9,1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };
// Permuted choice 2 (PC-2) table
     const int PC2[] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
    };
// Shifts table
     const int shifts[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
    };

     uint64_t keys[16];

uint64_t Permuted_ch1(uint64_t key64) {
    uint64_t key56 = 0;

    for (int i = 0; i < 56; i++) {
        int fromBit = 64 - PC1[i];         // convert PC1 position (from MSB)
        uint64_t bit = (key64 >> fromBit) & 1ULL;  // extract that bit
        key56 = (key56 << 1) | bit;        // build new key from left to right
    }

    return key56;  // 56-bit key (ready to split into C0/D0)
}
uint64_t Shift_circular(uint64_t key56, int round_no) {
    uint32_t left = key56 >> 28;
    uint32_t right = key56 & 0x0FFFFFFF;

    int shift = shifts[round_no - 1];  // 1 or 2 bits

    left = ((left << shift) | (left >> (28 - shift))) & 0x0FFFFFFF;
    right = ((right << shift) | (right >> (28 - shift))) & 0x0FFFFFFF;

    return ((uint64_t)left << 28) | right;
}

uint64_t Permuted_ch2(uint64_t key56) {
    uint64_t out_key_48 = 0;
    for(int i = 0; i < 48; i++) {
        int pos = PC2[i] - 1;
        uint64_t bit2 = (key56 >> (55 - pos)) & 1ULL;
        out_key_48 |= (bit2 << (47 - i));
    }
    return out_key_48;
}
void key_gen(uint64_t key) {
    uint64_t key56 = Permuted_ch1(key);
    uint64_t c_and_d = key56;

    for (int i = 0; i < 16; i++) {
        c_and_d = Shift_circular(c_and_d, i + 1);  // shift by the i-th round amount
        keys[i] = Permuted_ch2(c_and_d);
    }
}





// int main(void) {
//     uint64_t key = 0x0123456789ABCDEFULL;
//
//
//     uint64_t key56 = Permuted_ch1(key);
//     uint64_t shifted = Shift_circular(key56, 1);
//     uint64_t key48 = Permuted_ch2(shifted);
//
//     printf("Original key (64-bit): 0x%016llX\n", key);
//     printf("After PC-1 (56-bit):   0x%014llX\n", key56);
//     printf("After shifting:   0x%014llX\n", shifted);
//     printf("After PC-2 (48-bit):   0x%014llX\n", key48);
//     return 0;
//
// }
//0xF0CCAA0AACCF00
