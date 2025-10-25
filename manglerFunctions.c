#include "manglerFunctions.h"
#include <stdio.h>


//  Main Functions
uint64_t expansion_permutation(uint32_t R) {
    uint64_t output = 0;
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
    output |= ((uint64_t)(R & 0x1F)) << 1;            // bits 28-32 at positions 5-1
    output |= ((uint64_t)((R >> 31) & 0x01));         // bit 1 at position 0

    return output;
}
uint32_t p_box_permutation(uint32_t input) {
    uint32_t output = 0;
    // Manual bit by bit shifting is the fastest? all operations at compile time so pretty fast, faster than loop but idk if a lookup table would help.

    // P-box table: [16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25]
    // 32 is the LSB, 1 is the MSB

    output |= ((input >> 16) & 1) << 31;  // bit 16 → position 0
    output |= ((input >> 25) & 1) << 30;
    output |= ((input >> 12) & 1) << 29;
    output |= ((input >> 11) & 1) << 28;
    output |= ((input >> 3) & 1) << 27;
    output |= ((input >> 20) & 1) << 26;
    output |= ((input >> 4) & 1) << 25;
    output |= ((input >> 15) & 1) << 24;

    output |= ((input >> 31) & 1) << 23;
    output |= ((input >> 17) & 1) << 22;
    output |= ((input >> 9) & 1) << 21;
    output |= ((input >> 6) & 1) << 20;
    output |= ((input >> 27) & 1) << 19;
    output |= ((input >> 14) & 1) << 18;
    output |= ((input >> 1) & 1) << 17;
    output |= ((input >> 22) & 1) << 16;

    output |= ((input >> 30) & 1) << 15;
    output |= ((input >> 24) & 1) << 14;
    output |= ((input >> 8) & 1) << 13;
    output |= ((input >> 18) & 1) << 12;
    output |= ((input >> 32) & 1) << 11;
    output |= ((input >> 5) & 1) << 10;
    output |= ((input >> 29) & 1) << 9;
    output |= ((input >> 23) & 1) << 8;

    output |= ((input >> 13) & 1) << 7;
    output |= ((input >> 19) & 1) << 6;
    output |= ((input >> 2) & 1) << 5;
    output |= ((input >> 26) & 1) << 4;
    output |= ((input >> 10) & 1) << 3;
    output |= ((input >> 21) & 1) << 2;
    output |= ((input >> 28) & 1) << 1;
    output |= ((input >> 7) & 1) << 0;

    return output;
}

// Helper Functions
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