//
// Created by Sofyan Aarrass on 16/07/2022.
//

#include <cstdlib>
#include "../include/cpu.h"
#include "../include/instructions/instruction.h"

bool Cpu::execute_next_instruction() {



    return false;
}

Cpu::Cpu(Bus *bus1) {
    bus = bus1;
    init_registers();
}

void Cpu::init_registers() {
    registers.r08_s.r = (uint32_t*)calloc(4, 1);
    registers.r08_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r09_s.r = (uint32_t*)calloc(4, 1);
    registers.r09_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r10_s.r = (uint32_t*)calloc(4, 1);
    registers.r10_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r11_s.r = (uint32_t*)calloc(4, 1);
    registers.r11_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r12_s.r = (uint32_t*)calloc(4, 1);
    registers.r12_s.r_fiq = (uint32_t*)calloc(4, 1);

    registers.r13_s.r_abt = (uint32_t*)calloc(4, 1);
    registers.r13_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r13_s.r_svc = (uint32_t*)calloc(4, 1);
    registers.r13_s.r_irq = (uint32_t*)calloc(4, 1);
    registers.r13_s.r_und = (uint32_t*)calloc(4, 1);

    registers.r14_s.r_abt = (uint32_t*)calloc(4, 1);
    registers.r14_s.r_fiq = (uint32_t*)calloc(4, 1);
    registers.r14_s.r_svc = (uint32_t*)calloc(4, 1);
    registers.r14_s.r_irq = (uint32_t*)calloc(4, 1);
    registers.r14_s.r_und = (uint32_t*)calloc(4, 1);

    registers.r00 = (uint32_t*)calloc(4, 1);
    registers.r01 = (uint32_t*)calloc(4, 1);
    registers.r02 = (uint32_t*)calloc(4, 1);
    registers.r03 = (uint32_t*)calloc(4, 1);
    registers.r04 = (uint32_t*)calloc(4, 1);
    registers.r05 = (uint32_t*)calloc(4, 1);
    registers.r06 = (uint32_t*)calloc(4, 1);
    registers.r07 = (uint32_t*)calloc(4, 1);
    registers.r08 = registers.r08_s.r;
    registers.r09 = registers.r09_s.r;
    registers.r10 = registers.r10_s.r;
    registers.r11 = registers.r11_s.r;
    registers.r12 = registers.r12_s.r;
    registers.SP = registers.r13_s.r_fiq;
    registers.LR = registers.r14_s.r_fiq;
    registers.PC = (uint32_t*)calloc(4, 1);
    registers.CPSR = (uint32_t*)calloc(4, 1);
    flags = reinterpret_cast<cpu_flags_t *>(registers.CPSR);

}
