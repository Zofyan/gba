//
// Created by Sofyan Aarrass on 16/07/2022.
//

#include <cstring>
#include <cstdlib>
#include "../include/bus.h"

void Bus::read(uint32_t address, uint8_t *buf, bus_width size) {
    memcpy(buf, &buffer[address], size);
}

void Bus::write(uint32_t address, uint8_t *buf, bus_width size) {
    memcpy(&buffer[address], buf, size);
}

Bus::Bus() {
    buffer = (uint8_t*)calloc(256 * MB, 1);
    wram_board = buffer + WRAM_BOARD_START;
    wram_chip = buffer + WRAM_CHIP_START;
    oam = buffer + OAM_START;
    vram = buffer + VRAM_START;
    obj_palette_ram = buffer + OBJ_PALETTE_START;
    gp_rom1 = buffer + GP_ROM1_START;
    gp_rom2 = buffer + GP_ROM2_START;
    gp_rom3 = buffer + GP_ROM3_START;
    sram = buffer + SRAM_START;
}
