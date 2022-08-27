//
// Created by Sofyan on 25/08/2022.
//

#include "doctest/doctest.h"
#include "../include/cpu.h"
#include "../include/instructions/arm_instruction.h"
#include "../include/helpers.h"
#include "test.h"


TEST_CASE("testing the MUL instruction") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 5;
    *cpu.registers.r02 = 6;
    *cpu.registers.r03 = 40;

    uint32_t inst = mul_instruction_int{0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        3,
                                        1,
                                        0b1001,
                                        2}.mul_instruction_int_t;

    ArmInstruction *instruction = ArmInstruction::GetInstruction(inst, &cpu);

    CHECK(typeid(*instruction) == typeid(BXInstruction(0, nullptr)));

}
