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

TEST_CASE("testing the ALU family instructions") { // https://problemkaputt.de/gbatek.htm#armopcodesdataprocessingalu
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;


    uint32_t inst;
    ArmInstruction *instruction;
    uint32_t expected_result;

    SUBCASE("AND") {
        SUBCASE("test flag setting"){
            *cpu.registers.r01 = 2;
            *cpu.registers.r02 = 1;
            cpu.flags->v = 0;
            cpu.flags->c = 1;
            cpu.flags->z = 0;
            cpu.flags->n = 1;
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
            CHECK((cpu.flags->v == 0));
            CHECK((cpu.flags->z == 1));
            CHECK((cpu.flags->n == 0));
            CHECK((cpu.flags->c == 0));

            *cpu.registers.r02 = 1;
            cpu.flags->v = 1;
            cpu.flags->c = 0;
            cpu.flags->z = 0;
            cpu.flags->n = 1;
            inst = alu_instruction_int_i_is_0{2,
                                              0,
                                              LSR,
                                              1,
                                              0,
                                              1,
                                              1,
                                              0b0000,
                                              0,
                                              0,
                                              AL}.alu_instruction_int_i_is_0_t;
            instruction = ArmInstruction::GetInstruction(inst, &cpu);
            instruction->run();
            CHECK((cpu.flags->v == 1));
            CHECK((cpu.flags->z == 1));
            CHECK((cpu.flags->n == 0));
            CHECK((cpu.flags->c == 1));

            *cpu.registers.r02 = 1;
            cpu.flags->v = 1;
            cpu.flags->c = 1;
            cpu.flags->z = 1;
            cpu.flags->n = 0;
            inst = alu_instruction_int_i_is_0{2,
                                              0,
                                              LSL,
                                              31,
                                              0,
                                              1,
                                              1,
                                              0b0000,
                                              0,
                                              0,
                                              AL}.alu_instruction_int_i_is_0_t;
            instruction = ArmInstruction::GetInstruction(inst, &cpu);
            instruction->run();
            CHECK((cpu.flags->v == 1));
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 1));
            CHECK((cpu.flags->c == 0));
        }
        SUBCASE("register operand") {
            *cpu.registers.r01 = 12345;
            *cpu.registers.r02 = 54321;
            SUBCASE("doing 12345(r1) & 54321") {
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
                expected_result = 12345 & 54321;
                CHECK(*cpu.registers.r00 == expected_result);
            }
            SUBCASE("shift by immediate"){

                SUBCASE("doing 12345(r1) & 54321, left shift logical 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = 54321;
                    inst = alu_instruction_int_i_is_0{2,
                                                      0,
                                                      LSL,
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
                    expected_result = 12345 & (54321 << 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & 54321, right shift logical 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = 54321;
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
                    expected_result = 12345 & (54321 >> 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & -54321, right shift arithmetic 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = -54321;
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
                    expected_result = 12345 & (-54321 >> 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & 4321, right rotate 7") {
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
            SUBCASE("shift by register"){
                *cpu.registers.r08 = 7;

                SUBCASE("doing 12345(r1) & 54321, left shift logical 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = 54321;
                    inst = alu_instruction_int_i_is_0{2,
                                                      1,
                                                      LSL,
                                                      8,
                                                      0,
                                                      1,
                                                      1,
                                                      0b0000,
                                                      0,
                                                      0,
                                                      AL}.alu_instruction_int_i_is_0_t;
                    instruction = ArmInstruction::GetInstruction(inst, &cpu);
                    instruction->run();
                    expected_result = 12345 & (54321 << 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & 54321, right shift logical 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = 54321;
                    inst = alu_instruction_int_i_is_0{2,
                                                      1,
                                                      1,
                                                      8,
                                                      0,
                                                      1,
                                                      1,
                                                      0b0000,
                                                      0,
                                                      0,
                                                      AL}.alu_instruction_int_i_is_0_t;
                    instruction = ArmInstruction::GetInstruction(inst, &cpu);
                    instruction->run();
                    expected_result = 12345 & (54321 >> 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & -54321, right shift arithmetic 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = -54321;
                    inst = alu_instruction_int_i_is_0{2,
                                                      1,
                                                      2,
                                                      8,
                                                      0,
                                                      1,
                                                      1,
                                                      0b0000,
                                                      0,
                                                      0,
                                                      AL}.alu_instruction_int_i_is_0_t;
                    instruction = ArmInstruction::GetInstruction(inst, &cpu);
                    instruction->run();
                    expected_result = 12345 & (-54321 >> 7);
                    CHECK(*cpu.registers.r00 == expected_result);
                }

                SUBCASE("doing 12345(r1) & 4321, right rotate 7") {
                    *cpu.registers.r01 = 12345;
                    *cpu.registers.r02 = 4321;
                    inst = alu_instruction_int_i_is_0{2,
                                                      1,
                                                      3,
                                                      8,
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
        }

        SUBCASE("immediate operand") {
            *cpu.registers.r01 = 12345;
            SUBCASE("doing 12345(r1) & 49") {
                inst = alu_instruction_int_i_is_1{49,
                                                  0,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  1,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_1_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & 49;
                CHECK(*cpu.registers.r00 == expected_result);
            }
            SUBCASE("doing 12345(r1) & 6, ror-shift 1(2)") {

                inst = alu_instruction_int_i_is_1{6,
                                                  1,
                                                  0,
                                                  1,
                                                  1,
                                                  0b0000,
                                                  1,
                                                  0,
                                                  AL}.alu_instruction_int_i_is_1_t;
                instruction = ArmInstruction::GetInstruction(inst, &cpu);
                instruction->run();
                expected_result = 12345 & 2147483649;
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
