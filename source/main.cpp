//
// Created by Sofyan Aarrass on 18/07/2022.
//

#include <iostream>
#include <bitset>
#include "../include/emu.h"
#include "../include/helpers.h"
#include "../include/instructions/arm_instruction.h"

int main(){
    ArmInstruction *a;
    a = ArmInstruction::GetInstruction(0b11100001001011111111111100010000, nullptr);
    a->run();
    exit(0);
    FILE *fp = fopen("../tests/suite.gba", "r");

    emu::boot_emu(fp);

    return 0;

}