//
// Created by Sofyan on 25/08/2022.
//

#include "../include/emu.h"
#include "../include/cpu.h"
#include "../include/bus.h"
#include "../include/clock.h"

void emu::boot_emu(FILE *fp) {
    auto *buf = static_cast<uint8_t *>(calloc(1024, 1));
    fread(buf, 1024, 1, fp);

    Bus bus;
    Cpu cpu(&bus);

    Clock clock(&cpu, 60);

    clock.run();
}
