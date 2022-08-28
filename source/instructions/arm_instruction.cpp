//
// Created by Sofyan on 26/08/2022.
//

#include <iostream>
#include "../../include/instructions/arm_instruction.h"
#include "bitset"
#include "regex"


ArmInstruction::ArmInstruction(uint32_t instruction, Cpu *cpu) : Instruction() {
    condition = Condition(LARGEST_N_BITS_SMALL(instruction, 4));
    this->cpu = cpu;
    this->instruction = instruction;
}

int ArmInstruction::run() {
    if(condition.flags.z == SET_OR && condition.flags.c == CLEAR_OR){
        if(cpu->flags->z || !cpu->flags->c) return 0;
        return -1;
    }
    if((condition.flags.z == SET_OR && cpu->flags->z) || (condition.flags.c == CLEAR_OR && !cpu->flags->c)) return 0;

    if(condition.flags.z == SET && !cpu->flags->z) return -1;
    if(condition.flags.z == CLEAR && cpu->flags->z) return -1;

    if(condition.flags.n == SET && !cpu->flags->n) return -1;
    if(condition.flags.n == CLEAR && cpu->flags->n) return -1;

    if(condition.flags.c == SET && !cpu->flags->c) return -1;
    if(condition.flags.c == CLEAR && cpu->flags->c) return -1;

    if(condition.flags.v == SET && !cpu->flags->v) return -1;
    if(condition.flags.v == CLEAR && cpu->flags->v) return -1;

    if(condition.flags.n == EQUAL && condition.flags.v == EQUAL && (cpu->flags->v != cpu->flags->n)) return -1;
    if(condition.flags.n == NOT_EQUAL && condition.flags.v == NOT_EQUAL && (cpu->flags->v == cpu->flags->n)) return -1;

    return 0;
}

ArmInstruction* ArmInstruction::GetInstruction(uint32_t instruction, Cpu *cpu) {
    if(regex_match(static_cast<std::bitset<32>>(instruction).to_string(), std::regex(BXInstruction::operator_mask))){
        return new BXInstruction(instruction, cpu);
    }
    if(regex_match(std::bitset<32>(instruction).to_string(), std::regex(MULInstruction::operator_mask))){
        return new MULInstruction(instruction, cpu);
    }
    throw UnknownInstruction();
}

BXInstruction::BXInstruction(uint32_t instruction, Cpu *cpu) : ArmInstruction(instruction, cpu){};

int BXInstruction::run() {
    if(ArmInstruction::run()) return -1;

    cpu->cpu_mode = instruction & 0x1 ? THUMB : ARM;
    cpu->registers.PC = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 0));
    return 0;
}


MULInstruction::MULInstruction(uint32_t instruction, Cpu *cpu) : ArmInstruction(instruction, cpu){}

int MULInstruction::run() {
    if(ArmInstruction::run()) return -1;

    cpu_register *rd = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 16));
    cpu_register *rn = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 12));
    cpu_register *rs = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 8));
    cpu_register *rm = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 0));

    uint8_t A = GET_1_BIT_FROM_32_BITS(instruction, 21);
    *rd = *rs * *rm + (A ? *rn : 0);

    if(GET_1_BIT_FROM_32_BITS(instruction, 20)){
        cpu->flags->n = GET_1_BIT_FROM_32_BITS(*rd, 31);
        cpu->flags->z = *rd == 0;
    }
    return 0;
}
