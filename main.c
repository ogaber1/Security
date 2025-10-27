#include <stdint.h>
#include <stdio.h>
#include "manglerFunctions.h"


int main(void) {

    uint32_t input = 0xAAAAAAAA;

    uint64_t sbox_input = 0x1B02EFFC7072;

    printf("Input (32 bits): 0x%08X\n", input);
    printf("Binary: \n");
    print_binary_32(input);
    printf("\n");


    uint64_t exp_output = expansion_permutation(input);
    uint32_t pbox_output=p_box_permutation(input);
    uint32_t sbox_output=s_box_substitution(sbox_input);


    printf("Expanded Output (48 bits): 0x%012llX\n", exp_output);
    printf("Binary: \n");
    print_binary_48(exp_output);

    printf("P-Box Permutation Output (32 bits): 0x%08X\n", pbox_output);
    printf("Binary: \n");
    print_binary_32(pbox_output);


    printf("S-Box Substitution Input (48 bits): 0x%12llX\n", sbox_input);
    printf("Binary: \n");
    for (int i = 47; i >= 0; i--) {
        printf("%d ", (int)((sbox_input >> i) & 1));
        if (i%6==0) {
            printf("\n");
        }
    }
    printf("\n");

    printf("S-Box Substitution Output (32 bits): 0x%08X\n", sbox_output);
    printf("Binary: \n");
    print_binary_32(sbox_output);

    return 0;
}