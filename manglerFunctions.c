#include "manglerFunctions.h"
#include <stdio.h>

uint64_t expansion_permutation(uint32_t R) {
    uint64_t output = 0;
    //
    // Row 1: DES bits [32, 1, 2, 3, 4, 5] -> Output positions [47-42]
    output |= ((uint64_t)(R & 0x01)) << 47;           // bit 32
    output |= ((uint64_t)((R >> 27) & 0x1F)) << 42;   // bits 1-5

    // Row 2: DES bits [4, 5, 6, 7, 8, 9] -> Output positions [41-36]
    output |= ((uint64_t)((R >> 23) & 0x3F)) << 36;

    // Row 3: DES bits [8, 9, 10, 11, 12, 13] -> Output positions [35-30]
    output |= ((uint64_t)((R >> 19) & 0x3F)) << 30;

    // Row 4: DES bits [12, 13, 14, 15, 16, 17] -> Output positions [29-24]
    output |= ((uint64_t)((R >> 15) & 0x3F)) << 24;

    // Row 5: DES bits [16, 17, 18, 19, 20, 21] -> Output positions [23-18]
    output |= ((uint64_t)((R >> 11) & 0x3F)) << 18;

    // Row 6: DES bits [20, 21, 22, 23, 24, 25] -> Output positions [17-12]
    output |= ((uint64_t)((R >> 7) & 0x3F)) << 12;

    // Row 7: DES bits [24, 25, 26, 27, 28, 29] -> Output positions [11-6]
    output |= ((uint64_t)((R >> 3) & 0x3F)) << 6;

    // Row 8: DES bits [28, 29, 30, 31, 32, 1] -> Output positions [5-0]
    // Need: bits 28-32 (5 bits) at positions 5-1, and bit 1 at position 0
    output |= ((uint64_t)(R & 0x1F)) << 1;            // bits 28-32 at positions 5-1
    output |= ((uint64_t)((R >> 31) & 0x01));         // bit 1 at position 0

    return output;
}

void print_binary_32(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d ", (n >> i) & 1);
        if (i % 4 == 0) printf("\n");;
    }
    printf("\n");
}

void print_binary_48(uint64_t n) {
    for (int i = 47; i >= 0; i--) {
        printf("%d ", (int)((n >> i) & 1));
        if (i % 6 == 0) printf("\n");;
    }
    printf("\n");
}

void print_binary_64(uint64_t n){
    for (int i = 63; i >= 0; i--) {
        printf("%d ", (int)((n >> i) & 1));
        if (i % 8 == 0) printf("\n");;
    }
    printf("\n");
}