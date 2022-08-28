//
// Created by Sofyan on 28/08/2022.
//

#include "doctest/doctest.h"
#include "../include/cpu.h"
#include "../include/instructions/arm_instruction.h"
#include "test.h"

TEST_CASE("testing the BX instruction") {
    Cpu cpu = Cpu(nullptr);

    ArmInstruction *instruction;
    uint32_t inst;

    inst = 0b00000001001011111111111100010001;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(cpu.cpu_mode == THUMB);

    inst = 0b00000001001011111111111100010000;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(cpu.cpu_mode == ARM);


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
                               0}.mul_instruction_int_t;

    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(*cpu.registers.r00 == 30);

    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
                               0,
                               0}.mul_instruction_int_t;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(*cpu.registers.r00 == 70);
    CHECK((cpu.flags->n == 0));
    CHECK((cpu.flags->z == 0));

    *cpu.registers.r03 = -40;
    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
                               0,
                               0}.mul_instruction_int_t;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(*cpu.registers.r00 == -10);
    CHECK((cpu.flags->n == 1));
    CHECK((cpu.flags->z == 0));

    *cpu.registers.r03 = -30;
    inst = mul_instruction_int{2,
                               0b1001,
                               1,
                               3,
                               0,
                               1,
                               1,
                               0,
                               0}.mul_instruction_int_t;
    instruction = ArmInstruction::GetInstruction(inst, &cpu);
    instruction->run();
    CHECK(*cpu.registers.r00 == 0);
    CHECK((cpu.flags->n == 0));
    CHECK((cpu.flags->z == 1));
}
