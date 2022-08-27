//
// Created by Sofyan Aarrass on 16/07/2022.
//

#ifndef GBA_BUS_H
#define GBA_BUS_H

#define KB 1024
#define MB 1024 * 1024

#define BIOS_START 0x0
#define BIOS_SIZE 16 * KB
#define WRAM_BOARD_START 0x02000000
#define WRAM_BOARD_SIZE 256 * KB
#define WRAM_CHIP_START 0x03000000
#define WRAM_CHIP_SIZE 32 * KB
#define OBJ_PALETTE_START 0x05000000
#define OBJ_PALETTE_SIZE 1 * KB
#define VRAM_START 0x06000000
#define VRAM_SIZE 96 * KB
#define OAM_START 0x07000000
#define OAM_SIZE 1 * KB
#define GP_ROM1_START 0x08000000
#define GP_ROM1_SIZE 32 * MB
#define GP_ROM2_START 0x0A000000
#define GP_ROM2_SIZE 32 * MB
#define GP_ROM3_START 0xC8000000
#define GP_ROM3_SIZE 32 * MB
#define SRAM_START 0x0E000000
#define SRAM_SIZE 64 * KB
#define IO_START 0x04000000
#define IO_SIZE 0x3FF

enum bus_width {
    BYTE = 1,
    HALF_WORD = 2,
    WORD = 4
};

#include <cstdint>

class Bus {
public:
    Bus();
    void read(uint32_t address, uint8_t *buffer, bus_width size = BYTE);
    void write(uint32_t address, uint8_t *buffer, bus_width size = BYTE);

private:
    int cycles_to_wait = 0;
    uint8_t *buffer;
    uint8_t *bios;
    uint8_t *wram_board;
    uint8_t *wram_chip;
    uint8_t *obj_palette_ram;
    uint8_t *vram;
    uint8_t *oam;
    uint8_t *gp_rom1;
    uint8_t *gp_rom2;
    uint8_t *gp_rom3;
    uint8_t *sram;


};


#endif //GBA_BUS_H
