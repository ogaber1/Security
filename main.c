#include <stdint.h>
#include <stdio.h>

#define plaintext 0x4E6F772069732074
#define k 0x0123456789ABCDEF


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


    // The 8 S-boxes
    const int S_BOX[8][4][16] = {
        // S-box 1
        {
            {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
            { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
            { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
            {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
        },
        // S-box 2
        {
            {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
            { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
            { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
            {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
        },
        // S-box 3
        {
            {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
            {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
            {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
            { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
        },
        // S-box 4
        {
            { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
            {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
            {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
            { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
        },
        // S-box 5
        {
            { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
            {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
            { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
            {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
        },
        // S-box 6
        {
            {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
            {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
            { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
            { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
        },
        // S-box 7
        {
            { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
            {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
            { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
            { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
        },
        // S-box 8
        {
            {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
            { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
            { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
            { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
        }
    };


    uint64_t encrypt(uint64_t p);
    uint64_t decrypt(uint64_t c);
    uint64_t initial_permutation(uint64_t block);
    uint64_t Permuted_ch1(uint64_t key64);
    uint64_t Shift_circular(uint64_t key56,int round_no) ;
    uint64_t Permuted_ch2(uint64_t key56);
    void key_gen(uint64_t key);
    uint64_t expansion_permutation(uint32_t R);
    uint32_t p_box_permutation(uint32_t input);
    uint32_t s_box_substitution(uint64_t input_48bits);
    uint64_t inverse_permutation(uint64_t block);
    uint64_t swap(uint64_t block);


int main(void) {

    key_gen(k);
    uint64_t cipher = encrypt(plaintext);
    printf("Output = 0x%016llx\n", (unsigned long long)cipher);
    printf("Output = 0x%016llx\n", (unsigned long long)decrypt(cipher));

    return 0;
}


    uint64_t encrypt(uint64_t p){
        uint64_t output_initial_permutation= initial_permutation(p);

        for (int i = 0; i <16; i++) {
            uint32_t left = (uint32_t)(output_initial_permutation >> 32);
            uint32_t right = (uint32_t)(output_initial_permutation & 0xFFFFFFFFU);

            uint64_t output_expansion = expansion_permutation(right);

            uint64_t output_xor=output_expansion^keys[i];

            uint32_t output_sbox = s_box_substitution(output_xor);
            uint32_t output_p = p_box_permutation(output_sbox);

            uint32_t output_r1 = left^output_p;

            output_initial_permutation = (uint64_t)right<<32;
            output_initial_permutation |=output_r1;

        }
        uint64_t swapped = swap(output_initial_permutation);
        uint64_t ciphertext =inverse_permutation(swapped);
        return ciphertext;
    }
    uint64_t decrypt(uint64_t c) {
        uint64_t output_initial_permutation_d= initial_permutation(c);

        for (int i = 15; i >=0; i--) {
            uint32_t left = (uint32_t)(output_initial_permutation_d >> 32);
            uint32_t right = (uint32_t)(output_initial_permutation_d & 0xFFFFFFFFU);

            uint64_t output_expansion = expansion_permutation(right);

            uint64_t output_xor=output_expansion^keys[i];

            uint32_t output_sbox = s_box_substitution(output_xor);
            uint32_t output_p = p_box_permutation(output_sbox);

            uint32_t output_r1 = left^output_p;

            output_initial_permutation_d = (uint64_t)right<<32;
            output_initial_permutation_d |=output_r1;


        }
        uint64_t swapped_d = swap(output_initial_permutation_d);
        uint64_t plaintext_d =inverse_permutation(swapped_d);
        return plaintext_d;
    }
    inline uint64_t initial_permutation(uint64_t block)
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
    uint32_t s_box_substitution(uint64_t input_48bits) {
        uint32_t output = 0;

        // Split into 8 6-bit chunks, loop over the 8 and find reference in LUT, would unrolling the loop to 8 blocks  separate loops be faster?
        for (int box = 0; box < 8; box++) {
            // Extract 6-bit block
            int shift = (7 - box) * 6;  // 42, 36, 30, 24, 18, 12, 6, 0
            uint64_t six_bits = (input_48bits >> shift) & 0x3F;

            // Extract row (outer 2 bits: bit 5 and bit 0)
            int row = ((six_bits >> 5) & 0x1) << 1 | (six_bits & 0x1);
            // row = (bit5 << 1) | bit0

            // Extract column (middle 4 bits: bits 4-1)
            int col = (six_bits >> 1) & 0x0F;  // 0x0F = 0b1111

            // Lookup and append
            int s_output = S_BOX[box][row][col];  // Returns 4-bit value (0-15)
            output |= (s_output << ((7 - box) * 4));
        }

        return output;
    }
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
    uint64_t swap(uint64_t block){

    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFFU);

    return ((uint64_t)right << 32) | (uint64_t)left;
}
