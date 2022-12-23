//
// Created by Sofyan on 26/08/2022.
//

#ifndef GBE_ARM_INSTRUCTION_H
#define GBE_ARM_INSTRUCTION_H

#include "instruction.h"
#include "condition.h"
#include "vector"
#include "../helpers.h"
#include "../cpu.h"
#include "regex"

typedef enum shift{
    LSL = 0,
    LSR = 1,
    ASR = 2,
    ROR = 3
} shift_t;


class ArmInstruction: public Instruction {
protected:
    Cpu *cpu;
    uint32_t instruction;
public:
    static ArmInstruction* GetInstruction(uint32_t instruction, Cpu *cpu);
    static std::string operator_mask;

    ArmInstruction(uint32_t instruction, Cpu *cpu);
    Condition condition{AL};

    virtual int run();

};

class BXInstruction: public ArmInstruction {
public:
    inline static std::string operator_mask = "....000100101111111111110001....";
    BXInstruction(uint32_t instruction, Cpu *cpu);
    int run();

};

class MULInstruction: public ArmInstruction {
public:
    inline static std::string operator_mask = "....000.................1001....";
    MULInstruction(uint32_t instruction, Cpu *cpu);
    int run();

};

class ALUInstruction: public ArmInstruction {
public:
    inline static std::string operator_mask = "....00..........................";
    ALUInstruction(uint32_t instruction, Cpu *cpu);
    int run();

};



#endif //GBE_ARM_INSTRUCTION_H
