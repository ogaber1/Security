#include <stdint.h>
#include <stdio.h>
#include "manglerFunctions.h"

int main(void) {

    uint32_t input = 0x80000000;

    printf("Input (32 bits): 0x%08X\n", input);
    printf("Binary: \n");
    print_binary_32(input);
    printf("\n");

    uint64_t output = expansion_permutation(input);

    printf("Output (48 bits): 0x%012llX\n", output);
    printf("Binary: \n");
    print_binary_48(output);
    return 0;
}