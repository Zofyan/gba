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
#define TWO_32BITS_TO_64BIT(a, b) ((uint64_t)a  << 32 | b)

TEST_CASE("testing the BX instruction") {
    Cpu cpu = Cpu(nullptr);

    ArmInstruction *instruction;
    uint32_t inst;

    inst = 0b11100001001011111111111100010001;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    SUBCASE("BX sets thumb ") { CHECK(cpu.cpu_mode == THUMB); }

    inst = 0b11100001001011111111111100010000;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    SUBCASE("BX sets arm ") { CHECK(cpu.cpu_mode == ARM); }


}

TEST_CASE("testing the MUL family instructions") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 5;
    *cpu.registers.r02 = 6;
    *cpu.registers.r03 = 40;

    uint32_t inst;
    ArmInstruction *instruction;

    SUBCASE("MUL") {
        inst = mul_instruction_int{2,
                                   0b1001,
                                   1,
                                   3,
                                   0,
                                   0,
                                   0b0000,
                                   0,
                                   AL}.mul_instruction_int_t;

        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("doing 5 * 6 ") { CHECK(*cpu.registers.r00 == 30); }
    }
    SUBCASE("MLA") {
        inst = mul_instruction_int{2,
                                   0b1001,
                                   1,
                                   3,
                                   0,
                                   1,
                                   0b0001,
                                   0,
                                   AL}.mul_instruction_int_t;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("doing 5 * 6 + 40 ") {
            CHECK(*cpu.registers.r00 == 70);
            CHECK((cpu.flags->n == 0));
            CHECK((cpu.flags->z == 0));
        }
        *cpu.registers.r03 = -40;
        instruction->run();
        SUBCASE("doing 5 * 6 - 40 ") {
            CHECK(*cpu.registers.r00 == -10);
            CHECK((cpu.flags->n == 1));
            CHECK((cpu.flags->z == 0));
        }

        *cpu.registers.r03 = -30;
        instruction->run();
        SUBCASE("doing 5 * 6 - 30 ") {
            CHECK(*cpu.registers.r00 == 0);
            CHECK((cpu.flags->n == 0));
            CHECK((cpu.flags->z == 1));
        }
    }

    SUBCASE("UMAAL") {
        inst = mul_instruction_int{2,
                                   0b1001,
                                   3,
                                   1,
                                   0,
                                   1,
                                   0b0010,
                                   0,
                                   AL}.mul_instruction_int_t;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 0xFFFFFFFF;
        *cpu.registers.r03 = 0xFFFFFFFF;
        cpu.flags->n = 0;
        cpu.flags->z = 1;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, negative and doesnt set flags") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = (uint64_t) 0xFFFFFFFF * (uint64_t) 0xFFFFFFFF;
            CHECK(result == expected_result);
            CHECK((cpu.flags->n == 0));
            CHECK((cpu.flags->z == 1));
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 30;
        *cpu.registers.r03 = (1 << 30) + 100;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = ((uint64_t) 1 << 30) * (((uint64_t) 1 << 30) + 100);
            CHECK(result == expected_result);
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 31;
        *cpu.registers.r03 = 0;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, result is 0 ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = 0;
            CHECK(result == expected_result);
        }

        *cpu.registers.r00 = 5;
        *cpu.registers.r01 = 6;
        *cpu.registers.r02 = 1 << 30;
        *cpu.registers.r03 = (1 << 30) + 100;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result and some inital value in both starting registers ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = (uint64_t) 1 << 30;
            expected_result *= (1 << 30) + 100;
            expected_result += 5 + 6;
            CHECK(result == expected_result);
        }
    }
    SUBCASE("UMULL"){
        inst = mul_instruction_int{2,
                                   0b1001,
                                   3,
                                   1,
                                   0,
                                   1,
                                   0b0100,
                                   0,
                                   AL}.mul_instruction_int_t;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);

        *cpu.registers.r00 = 5;
        *cpu.registers.r01 = 6;
        *cpu.registers.r02 = 1 << 31;
        *cpu.registers.r03 = 0;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, result is 0 ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = 0;
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 1));
            CHECK((cpu.flags->n == 0));
        }
        *cpu.registers.r00 = 5;
        *cpu.registers.r01 = 6;
        *cpu.registers.r02 = 0xFFFFFFFF;
        *cpu.registers.r03 = 0xFFFFFFFF;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, negative") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = (uint64_t) 0xFFFFFFFF * (uint64_t) 0xFFFFFFFF;
            CHECK(result == expected_result);
            CHECK((cpu.flags->n == 1));
            CHECK((cpu.flags->z == 0));
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 31;
        *cpu.registers.r03 = 128;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE(" doing a 32*32 bit with 64 bit result, result Lo is 0 ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = 1;
            expected_result <<= 31;
            expected_result *= 128;
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 0));
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 30;
        *cpu.registers.r03 = (1 << 30) + 100;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = ((uint64_t) 1 << 30) * (((uint64_t) 1 << 30) + 100);
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 0));
        }
    }
    SUBCASE("UMLAL"){
        inst = mul_instruction_int{2,
                                   0b1001,
                                   3,
                                   1,
                                   0,
                                   1,
                                   0b0101,
                                   0,
                                   AL}.mul_instruction_int_t;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 31;
        *cpu.registers.r03 = 0;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, result is 0 ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = 0;
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 1));
            CHECK((cpu.flags->n == 0));
        }
        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 0xFFFFFFFF;
        *cpu.registers.r03 = 0xFFFFFFFF;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result, negative") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = (uint64_t) 0xFFFFFFFF * (uint64_t) 0xFFFFFFFF;
            CHECK(result == expected_result);
            CHECK((cpu.flags->n == 1));
            CHECK((cpu.flags->z == 0));
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 31;
        *cpu.registers.r03 = 128;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE(" doing a 32*32 bit with 64 bit result, result Lo is 0 ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = 1;
            expected_result <<= 31;
            expected_result *= 128;
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 0));
        }

        *cpu.registers.r00 = 0;
        *cpu.registers.r01 = 0;
        *cpu.registers.r02 = 1 << 30;
        *cpu.registers.r03 = (1 << 30) + 100;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = (1ll << 30) * (((uint64_t) 1 << 30) + 100);
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 0));
        }

        *cpu.registers.r00 = 5;
        *cpu.registers.r01 = 6;
        *cpu.registers.r02 = 1 << 30;
        *cpu.registers.r03 = (1 << 30) + 100;
        instruction->run();
        SUBCASE("doing a 32*32 bit with 64 bit result with numbers in both result registers ") {
            uint64_t result = TWO_32BITS_TO_64BIT(*cpu.registers.r00, *cpu.registers.r01);

            uint64_t expected_result = ((5ll << 32) | 6) + ((uint64_t) 1 << 30) * (((uint64_t) 1 << 30) + 100);
            CHECK(result == expected_result);
            CHECK((cpu.flags->z == 0));
            CHECK((cpu.flags->n == 0));
        }
    }
}
