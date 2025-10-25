#ifndef MANGLERFUNCTIONS_H
#define MANGLERFUNCTIONS_H

#include <stdint.h>

uint64_t expansion_permutation(uint32_t R);

uint32_t p_box_permutation(uint32_t input);

//Helper Functions
void print_binary_32(uint32_t n);
void print_binary_48(uint64_t n);
void print_binary_64(uint64_t n);

#endif //MANGLERFUNCTIONS_H
