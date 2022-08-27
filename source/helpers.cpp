//
// Created by Sofyan on 27/08/2022.
//

//
// Created by Sofyan on 26/08/2022.
//

#ifndef GBE_HELPERS_H
#define GBE_HELPERS_H

#include <cassert>
#include <cstdint>
#include "../include/helpers.h"
#include "../include/cpu.h"

cpu_register* number_to_register(Cpu *cpu, uint8_t n){
    switch (n) {
        case 0:
            return cpu->registers.r00;
        case 1:
            return cpu->registers.r01;
        case 2:
            return cpu->registers.r02;
        case 3:
            return cpu->registers.r03;
        case 4:
            return cpu->registers.r04;
        case 5:
            return cpu->registers.r05;
        case 6:
            return cpu->registers.r06;
        case 7:
            return cpu->registers.r07;
        case 8:
            return cpu->registers.r08;
        case 9:
            return cpu->registers.r09;
        case 10:
            return cpu->registers.r10;
        case 11:
            return cpu->registers.r11;
        case 12:
            return cpu->registers.r12;
        case 13:
            return cpu->registers.SP;
        case 14:
            return cpu->registers.LR;
        case 15:
            return cpu->registers.PC;
        default:
            assert(false);
            return 0;
    }
}

#endif //GBE_HELPERS_H
