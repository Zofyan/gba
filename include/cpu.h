//
// Created by Sofyan Aarrass on 16/07/2022.
//

#ifndef GBA_CPU_H
#define GBA_CPU_H


#include "bus.h"

typedef uint32_t cpu_register;

enum user_types{
    System,
    FIQ,
    Supervisor,
    IRQ,
    Undefined
};

typedef struct registers{
    cpu_register *r00;
    cpu_register *r01;
    cpu_register *r02;
    cpu_register *r03;
    cpu_register *r04;
    cpu_register *r05;
    cpu_register *r06;
    cpu_register *r07;
    cpu_register *r08;
    cpu_register *r09;
    cpu_register *r10;
    cpu_register *r11;
    cpu_register *r12;
    cpu_register *PC;
    cpu_register *LR;
    cpu_register *SP;
    cpu_register *CPSR;
    struct r08_s{
        cpu_register *r;
        cpu_register *r_fiq;
    } r08_s;
    struct r09_s{
        cpu_register *r;
        cpu_register *r_fiq;
    } r09_s;
    struct r10_s{
        cpu_register *r;
        cpu_register *r_fiq;
    } r10_s;
    struct r11_s{
        cpu_register *r;
        cpu_register *r_fiq;
    } r11_s;
    struct r12_s{
        cpu_register *r;
        cpu_register *r_fiq;
    } r12_s;
    struct r13_s{
        cpu_register *r_fiq;
        cpu_register *r_svc;
        cpu_register *r_abt;
        cpu_register *r_irq;
        cpu_register *r_und;
    } r13_s;
    struct r14_s{
        cpu_register *r_fiq;
        cpu_register *r_svc;
        cpu_register *r_abt;
        cpu_register *r_irq;
        cpu_register *r_und;
    } r14_s;
} registers_t;

typedef struct cpu_flags{
    uint32_t n : 1;
    uint32_t z : 1;
    uint32_t c : 1;
    uint32_t v : 1;
    uint32_t q : 1;
    uint32_t reserved0 : 2;
    uint32_t j : 1;
    uint32_t reserved1 : 13;
    uint32_t e : 1;
    uint32_t a : 1;
    uint32_t i : 1;
    uint32_t f : 1;
    uint32_t t : 1;
    uint32_t m4m0 : 4;
} cpu_flags_t;

enum cpu_mode_t{
    ARM,
    THUMB
};

class Cpu {
public:
    Bus *bus;
    cpu_mode_t cpu_mode = ARM;
    registers_t registers;
    cpu_flags_t *flags;

    bool keep_running = true;

    Cpu(Bus *bus1);
    bool execute_next_instruction();

private:
    void init_registers();


};


#endif //GBA_CPU_H
