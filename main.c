#include <stdint.h>
#include <stdio.h>
#include "manglerFunctions.h"
#include "IP_permutation.h"
#include "inverse_permutation.h"
#include "swap.h"
#include "key_scheduling.h"

#define plaintext 0x4E6F772069732074
#define key 0x0123456789ABCDEF

uint64_t encrypt(uint64_t p);
uint64_t decrypt(uint64_t c);

int main(void) {

    key_gen(key);
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