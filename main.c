#include <stdint.h>
#include <stdio.h>
#include "manglerFunctions.h"

int main(void) {

    uint32_t input = 0xAAAAAAAA;

    printf("Input (32 bits): 0x%08X\n", input);
    printf("Binary: \n");
    print_binary_32(input);
    printf("\n");

    uint64_t exp_output = expansion_permutation(input);
    uint32_t pbox_output=p_box_permutation(input);


    printf("Expanded Output (48 bits): 0x%012llX\n", exp_output);
    printf("Binary: \n");
    print_binary_48(exp_output);

    printf("P-Box Permutation Output (32 bits): 0x%08X\n", pbox_output);
    printf("Binary: \n");
    print_binary_32(pbox_output);

    return 0;
}