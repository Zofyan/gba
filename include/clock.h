//
// Created by Sofyan on 25/08/2022.
//

#ifndef GBE_CLOCK_H
#define GBE_CLOCK_H

#include "cpu.h"

class Clock {
public:
    Clock(Cpu *cpu, int fps);
    void run();
private:
    int fps;
    Cpu *cpu;
};


#endif //GBE_CLOCK_H
