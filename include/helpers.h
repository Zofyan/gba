//
// Created by Sofyan on 26/08/2022.
//

#ifndef GBE_HELPERS_H
#define GBE_HELPERS_H

#include <cassert>
#include "cpu.h"
struct UnknownInstruction : public std::exception {};
template<typename T> T SMALLEST_N_BITS_SMALL(T x, uint32_t n){ return static_cast<T>((x << (sizeof(x) * 8 - n))) >> (sizeof(x) * 8 - n);}
template<typename T> T SMALLEST_N_BITS_BIG(T x, uint32_t n){ return x << (sizeof(x) * 8 - n);}
template<typename T> T LARGEST_N_BITS_BIG(T x, uint32_t n){ return static_cast<T>((x >> (sizeof(x) * 8 - n))) << (sizeof(x) * 8 - n);}
template<typename T> T LARGEST_N_BITS_SMALL(T x, uint32_t n){ return x >> (sizeof(x) * 8 - n);}

#define GET_8_BITS_FROM_32_BITS(x, n) ((x << (24 - n)) >> 24)
#define GET_5_BITS_FROM_32_BITS(x, n) ((x << (27 - n)) >> 27)
#define GET_4_BITS_FROM_32_BITS(x, n) ((x << (28 - n)) >> 28)
#define GET_2_BIT_FROM_32_BITS(x, n) ((x << (30 - n)) >> 30)
#define GET_1_BIT_FROM_32_BITS(x, n) ((x << (31 - n)) >> 31)

cpu_register* number_to_register(Cpu *cpu, uint8_t n);
#endif //GBE_HELPERS_H
