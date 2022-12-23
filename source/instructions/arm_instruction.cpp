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
    if(regex_match(std::bitset<32>(instruction).to_string(), std::regex(ALUInstruction::operator_mask))){
        return new ALUInstruction(instruction, cpu);
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

    uint8_t subcode = GET_4_BITS_FROM_32_BITS(instruction, 21);
    uint64_t temp;
    switch (subcode) {
        case 0b0000:
            *rd = *rs * *rm;
            break;
        case 0b0001:
            *rd = *rs * *rm + *rn;
            break;
        case 0b0010:
            temp = *rs;
            temp *= *rm;
            temp += *rd + *rn;

            *rd = (temp >> 32);
            *rn = temp;
            break;
        case 0b0100:
            temp = *rs;
            temp *= *rm;

            *rd = (temp >> 32);
            *rn = temp;
            break;
        case 0b0101:
            temp = *rs;
            temp *= *rm;
            temp += ((uint64_t)*rd << 32) | *rn;

            *rd = (temp >> 32);
            *rn = temp;
            break;
        default:
            assert(false);
            break;
    }

    if(GET_1_BIT_FROM_32_BITS(instruction, 20) && subcode != 0b0010){
        if(subcode > 1){
            cpu->flags->z = *rd == 0 && *rn == 0;
        } else {
            cpu->flags->z = *rd == 0;
        }
        cpu->flags->n = GET_1_BIT_FROM_32_BITS(*rd, 31);
    }
    return 0;
}

ALUInstruction::ALUInstruction(uint32_t instruction, Cpu *cpu) : ArmInstruction(instruction, cpu){}

int ALUInstruction::run() {
    if(ArmInstruction::run()) return -1;

    uint32_t first_operand, second_operand = 0;
    cpu_register *destination_register;
    uint8_t opcode;
    bool set_flags;

    opcode = GET_4_BITS_FROM_32_BITS(instruction, 21);
    first_operand = *number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 16));
    destination_register = number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 12));
    set_flags = GET_1_BIT_FROM_32_BITS(instruction, 20);

    shift_t shift_type;
    uint16_t shift_amount;

    if(GET_1_BIT_FROM_32_BITS(instruction, 25)){ // immediate second
        second_operand = GET_8_BITS_FROM_32_BITS(instruction, 0);
        shift_type = ROR;
        shift_amount = GET_4_BITS_FROM_32_BITS(instruction, 8) * 2;
    } else{ // register second
        second_operand = *number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 0));
        shift_type = static_cast<shift_t>(GET_2_BIT_FROM_32_BITS(instruction, 5));
        if(GET_1_BIT_FROM_32_BITS(instruction, 4)){ // shift by register
            assert(GET_1_BIT_FROM_32_BITS(instruction, 7) == 0);
            assert(GET_4_BITS_FROM_32_BITS(instruction, 8) < 15);
            shift_amount = (*number_to_register(cpu, GET_4_BITS_FROM_32_BITS(instruction, 8))) & 0xFF;
        } else{ // shift by immediate
            shift_amount = GET_5_BITS_FROM_32_BITS(instruction, 7);
        }
    }

    bool carry;
    switch(shift_type){
        case LSL:
            second_operand = second_operand << shift_amount;
            carry = (((1 << 31) >> shift_amount) & second_operand) != 0;
            break;
        case LSR:
        case ASR:
            second_operand = second_operand >> shift_amount;
            carry = ((1 << shift_amount) & second_operand) != 0;
            break;
        case ROR:
            second_operand = (second_operand >> shift_amount) | (second_operand << (32 - shift_amount));
            carry = ((1 << shift_amount) & second_operand) != 0;
            break;
    }

    switch (opcode) {
        case 0x0: // AND
            *destination_register = first_operand & (shift_type == ASR ? (int32_t)second_operand : second_operand);
            break;
        default:
            break;
    }

    if(set_flags){
        cpu->flags->z = *destination_register == 0;
        cpu->flags->n = *destination_register < 0;
        carry = shift_amount != 0 && carry;
        switch(opcode){
            case 0x0:
            case 0x1:
                cpu->flags->n = carry;
                break;
        }
    }
    return 0;
}
