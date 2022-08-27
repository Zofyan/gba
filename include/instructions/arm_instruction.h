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




class ArmInstruction: public Instruction {
protected:
    Cpu *cpu;
    uint32_t instruction;
public:
    static ArmInstruction GetInstruction(uint32_t instruction, Cpu *cpu);
    static std::string operator_mask;

    ArmInstruction(uint32_t instruction, Cpu *cpu);
    Condition condition = Condition(0);


    virtual int run();

};

class BXInstruction: public ArmInstruction {
public:
    inline static std::string operator_mask = "....000100101111111111110001....";
    BXInstruction(uint32_t instruction, Cpu *cpu);
    virtual int run();

};



#endif //GBE_ARM_INSTRUCTION_H
