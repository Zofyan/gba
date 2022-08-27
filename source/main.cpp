//
// Created by Sofyan Aarrass on 18/07/2022.
//

#include <iostream>
#include <bitset>
#include "../include/emu.h"
#include "../include/helpers.h"
#include "../include/instructions/arm_instruction.h"

int main(){
    uint32_t a = 0b00000000000000000000000011110000;
    std::bitset<32> b;
    a = GET_4_BITS_FROM_32_BITS(a, 4);
    b = a;
    std::cout << b.to_string() << "\n";
    exit(0);
    FILE *fp = fopen("../tests/suite.gba", "r");

    emu::boot_emu(fp);

    return 0;

}