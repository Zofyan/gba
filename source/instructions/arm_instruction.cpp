//
// Created by Sofyan on 26/08/2022.
//

#include "../../include/instructions/arm_instruction.h"
#include "bitset"
#include "regex"


ArmInstruction::ArmInstruction(uint32_t instruction, Cpu *cpu) : Instruction() {
    condition = Condition(LARGEST_N_BITS_SMALL(instruction, 4));
    this->cpu = cpu;
    this->instruction = instruction;
}

int ArmInstruction::run() {
    return 0;
}

ArmInstruction* ArmInstruction::GetInstruction(uint32_t instruction, Cpu *cpu) {
    if(regex_match(static_cast<std::bitset<32>>(instruction).to_string(), std::regex(BXInstruction::operator_mask))){
        return new BXInstruction(instruction, cpu);
    }
    throw UnknownInstruction();
}

BXInstruction::BXInstruction(uint32_t instruction, Cpu *cpu) : ArmInstruction(instruction, cpu){};

int BXInstruction::run() {
    if(ArmInstruction::run()) return -1;

    cpu->cpu_mode = instruction & 0x1 ? THUMB : ARM;
    cpu->registers.PC = number_to_register(cpu, instruction & 0x1111);
    return 0;
}


