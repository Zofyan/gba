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

TEST_CASE("testing the condition flags") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 5;
    *cpu.registers.r02 = 6;

    uint32_t inst;
    ArmInstruction *instruction;

    SUBCASE("instruction does not run") {
        BEFORE_TEST(&inst, EQ);
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition EQ") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, NE);
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition NE") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, CS);
        cpu.flags->c = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition CS/HS") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, CC);
        cpu.flags->c = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition CC/LO") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, MI);
        cpu.flags->n = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition MI") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, PL);
        cpu.flags->n = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition PL") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, VS);
        cpu.flags->v = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition VS") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, VC);
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition VC") { CHECK(*cpu.registers.r00 == 0); }

        BEFORE_TEST(&inst, HI);
        cpu.flags->c = 1;
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition HI") { CHECK(*cpu.registers.r00 == 0); };

        BEFORE_TEST(&inst, LS);
        cpu.flags->c = 1;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LS") { CHECK(*cpu.registers.r00 == 0); }

        BEFORE_TEST(&inst, GE);
        cpu.flags->n = 0;
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GE") { CHECK(*cpu.registers.r00 == 0); }

        BEFORE_TEST(&inst, LT);
        cpu.flags->n = 1;
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LT") { CHECK(*cpu.registers.r00 == 0); }

        BEFORE_TEST(&inst, GT);
        cpu.flags->n = 1;
        cpu.flags->v = 1;
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GT") { CHECK(*cpu.registers.r00 == 0); }
        BEFORE_TEST(&inst, GT);
        cpu.flags->n = 0;
        cpu.flags->v = 1;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GT") { CHECK(*cpu.registers.r00 == 0); }

        BEFORE_TEST(&inst, LE);
        cpu.flags->n = 0;
        cpu.flags->v = 0;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LE") { CHECK(*cpu.registers.r00 == 0); }
    }

    SUBCASE("instruction does run") {
        BEFORE_TEST(&inst, 0b0000);
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition EQ") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0001);
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition NE") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0010);
        cpu.flags->c = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition CS/HS") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0011);
        cpu.flags->c = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition CC/LO") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0100);
        cpu.flags->n = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition MI") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0101);
        cpu.flags->n = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition PL") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0110);
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition VS") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b0111);
        cpu.flags->v = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition VC") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, 0b1000);
        cpu.flags->c = 1;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition HI") { CHECK(*cpu.registers.r00 == 30); };

        BEFORE_TEST(&inst, 0b1001);
        cpu.flags->c = 0;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LS") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b1001);
        cpu.flags->c = 1;
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LS") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, 0b1010);
        cpu.flags->n = 1;
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GE") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b1010);
        cpu.flags->n = 0;
        cpu.flags->v = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GE") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, 0b1011);
        cpu.flags->n = 1;
        cpu.flags->v = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LT") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b1011);
        cpu.flags->n = 0;
        cpu.flags->v = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LT") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, 0b1100);
        cpu.flags->n = 1;
        cpu.flags->v = 1;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GT") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b1100);
        cpu.flags->n = 0;
        cpu.flags->v = 0;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition GT") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, 0b1101);
        cpu.flags->n = 1;
        cpu.flags->v = 0;
        cpu.flags->z = 0;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LE") { CHECK(*cpu.registers.r00 == 30); }
        BEFORE_TEST(&inst, 0b1101);
        cpu.flags->n = 0;
        cpu.flags->v = 0;
        cpu.flags->z = 1;
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition LE") { CHECK(*cpu.registers.r00 == 30); }

        BEFORE_TEST(&inst, AL);
        instruction = ArmInstruction::GetInstruction(inst, &cpu);
        instruction->run();
        SUBCASE("condition AL") { CHECK(*cpu.registers.r00 == 30); }
    }
}

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

TEST_CASE("testing the MUL instruction") {
    Cpu cpu = Cpu(nullptr);
    *cpu.registers.r00 = 0;
    *cpu.registers.r01 = 5;
    *cpu.registers.r02 = 6;
    *cpu.registers.r03 = 40;

    uint32_t inst;
    ArmInstruction *instruction;

    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               0,
                               0,
                               0,
                               AL}.mul_instruction_int_t;

    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    SUBCASE("doing 5 * 6 ") { CHECK(*cpu.registers.r00 == 30); }

    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
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
    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
                               0,
                               AL}.mul_instruction_int_t;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    SUBCASE("doing 5 * 6 - 40 ") {
        CHECK(*cpu.registers.r00 == -10);
        CHECK((cpu.flags->n == 1));
        CHECK((cpu.flags->z == 0));
    }

    *cpu.registers.r03 = -30;
    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
                               0,
                               AL}.mul_instruction_int_t;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    SUBCASE("doing 5 * 6 - 30 ") {
        CHECK(*cpu.registers.r00 == 0);
        CHECK((cpu.flags->n == 0));
        CHECK((cpu.flags->z == 1));
    }
}
