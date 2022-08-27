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

cpu_register* number_to_register(Cpu *cpu, uint8_t n);

#endif //GBE_HELPERS_H
