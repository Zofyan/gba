//
// Created by Sofyan Aarrass on 16/07/2022.
//

#ifndef GBA_ROM_H
#define GBA_ROM_H

#include <cstdint>

typedef struct cart {
    uint32_t rom_entry_point;
    uint8_t nintendo_logo[156];
    uint8_t game_title[12];
    uint8_t game_code[4];
    uint8_t maker_code[2];
    uint8_t fixed_96h;
    uint8_t main_unit_code;
    uint8_t device_type;
    uint8_t zeros[7];
    uint8_t software_version;
    uint8_t complement_check;
    uint8_t zeros2[2];
    uint8_t extra[4 + 1 + 1 + 26 + 4];
    uint8_t data[];

} cart_t;

class rom {
    cart_t cart;
};


#endif //GBA_ROM_H
