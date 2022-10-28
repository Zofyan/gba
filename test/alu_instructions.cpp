//
// Created by Sofyan on 28/08/2022.
//

#include <bitset>
#include <iostream>
#include "doctest/doctest.h"
#include "../include/cpu.h"
#include "../include/instructions/arm_instruction.h"
#include "test.h"

#define TWO_32BITS_TO_64BIT(a, b) ((uint64_t)(a)  << 32 | (b))

TEST_CASE("testing the ALU family instructions") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 25;

    uint32_t inst;
    ArmInstruction *instruction;
    uint32_t expected_result;

    SUBCASE("AND") {
        SUBCASE("register operand") {
            SUBCASE("doing 25(r1) & 6") {
                *cpu.registers.r02 = 6;
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
                expected_result = 25 & 6;
                CHECK(*cpu.registers.r00 == expected_result);
            }

            SUBCASE("doing 25(r1) & 6, left shift logical 7") {
                *cpu.registers.r01 = 12345;
                *cpu.registers.r02 = 4321;
                inst = alu_instruction_int_i_is_0{2,
                                                  0,
                                                  0,
                                                  7,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_0_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & (4321 << 7);
                CHECK(*cpu.registers.r00 == expected_result);
            }

            SUBCASE("doing 25(r1) & 6, right shift logical 7") {
                *cpu.registers.r01 = 12345;
                *cpu.registers.r02 = 4321;
                inst = alu_instruction_int_i_is_0{2,
                                                  0,
                                                  1,
                                                  7,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_0_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & (4321 >> 7);
                CHECK(*cpu.registers.r00 == expected_result);
            }

            SUBCASE("doing 25(r1) & 6, right shift arithmetic 7") {
                *cpu.registers.r01 = 12345;
                *cpu.registers.r02 = -4321;
                inst = alu_instruction_int_i_is_0{2,
                                                  0,
                                                  2,
                                                  7,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_0_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & (-4321 >> 7);
                CHECK(*cpu.registers.r00 == expected_result);
            }

            SUBCASE("doing 25(r1) & 6, right rotate 7") {
                *cpu.registers.r01 = 12345;
                *cpu.registers.r02 = 4321;
                inst = alu_instruction_int_i_is_0{2,
                                                  0,
                                                  3,
                                                  7,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_0_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & (3254779937);
                CHECK(*cpu.registers.r00 == expected_result);
            }

        }

        SUBCASE("immediate operand") {
            SUBCASE("doing 25(r1) & 6") {
                inst = alu_instruction_int_i_is_1{6,
                                                  0,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_1_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                CHECK(*cpu.registers.r00 == expected_result);
            }
            SUBCASE("doing 25(r1) & 6, ror-shift 1(2)") {

                inst = alu_instruction_int_i_is_1{6,
                                                  1,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  0,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_1_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 25 & 2147483649;
                CHECK(*cpu.registers.r00 == expected_result);
            }
        }
    }

    SUBCASE("EOR") {
        SUBCASE("doing 25 & 6, immediate operand") {
            inst = alu_instruction_int_i_is_0{2,
                                              0,
                                              0,
                                              0,
                                              0,
                                              1,
                                              1,
                                              0x1,
                                              0,
                                              0,
                                              AL}.alu_instruction_int_i_is_0_t;

            instruction = ArmInstruction::GetInstruction(inst, &cpu);
            instruction->run();
            uint32_t expected_result = 25 & 6;
            CHECK(*cpu.registers.r00 == expected_result);
        }
    }
}
