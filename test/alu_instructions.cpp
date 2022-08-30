//
// Created by Sofyan on 28/08/2022.
//

#include <bitset>
#include <iostream>
#include "doctest/doctest.h"
#include "../include/cpu.h"
#include "../include/instructions/arm_instruction.h"
#include "test.h"

#define BEFORE_TEST(inst, a) (*(inst) = mul_instruction_int{2, 0b1001, 1, 0, 0, 0, 0, 0, a}.mul_instruction_int_t)
#define TWO_32BITS_TO_64BIT(a, b) ((uint64_t)(a)  << 32 | (b))

TEST_CASE("testing the ALU family instructions") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 25;
    *cpu.registers.r02 = 6;

    uint32_t inst;
    ArmInstruction *instruction;

    SUBCASE("AND") {
        inst = alu_instruction_int_i_is_0{2,
                                   0,
                                   0,
                                   0,
                                   0,
                                   1,
                                   1,
                                   0b0000,
                                   0,
                                   0,
                                   AL}.alu_instruction_int_i_is_0_t;

        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        uint32_t expected_result = 25 & 6;
        SUBCASE("doing 25 & 6 ") { CHECK(*cpu.registers.r00 == expected_result); }
    }
}
