//
// Created by Omar on 10/28/2025.
//
#ifndef KEY_SCHEDULING_H
#define KEY_SCHEDULING_H
#include <stdint.h>

extern const int PC1[];
// Permuted choice 2 (PC-2) table
extern const int PC2[];
// Shifts table
extern const int shifts[];

extern uint64_t keys[16];


uint64_t Permuted_ch1(uint64_t key64);
uint64_t Shift_circular(uint64_t key56,int round_no) ;
uint64_t Permuted_ch2(uint64_t key56);
void key_gen(uint64_t key);




#endif //KEY_SCHEDULING_H
