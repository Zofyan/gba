//
// Created by Sofyan Aarrass on 18/07/2022.
//

#include <iostream>
#include <bitset>
#include "../include/emu.h"
#include "../include/helpers.h"
#include "../include/instructions/arm_isntruction.h"

int main(){
    FILE *fp = fopen("../tests/suite.gba", "r");

    emu::boot_emu(fp);

    return 0;

}