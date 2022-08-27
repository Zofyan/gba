//
// Created by Sofyan on 25/08/2022.
//

#include "../include/clock.h"

void Clock::run() {
    while(cpu->keep_running){
        cpu->execute_next_instruction();
    }
}

Clock::Clock(Cpu *cpu, int fps) {
    this->cpu = cpu;
    this->fps = fps;
}
