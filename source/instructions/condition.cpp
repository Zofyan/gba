//
// Created by Sofyan on 26/08/2022.
//

#include <cassert>
#include "../../include/instructions/condition.h"

Condition::Condition(uint8_t code) {
    switch (code) {
        case 0b0000:
            flags = {IGNORE, IGNORE, IGNORE, SET};
            suffix = "EQ";
            description = "equal";
            break;
        case 0b0001:
            flags = {IGNORE, IGNORE, IGNORE, CLEAR};
            suffix = "NE";
            description = "not equal";
            break;
        case 0b0010:
            flags = {SET, IGNORE, IGNORE, IGNORE};
            suffix = "CS";
            description = "unsigned higher or same";
            break;
        case 0b0011:
            flags = {CLEAR, IGNORE, IGNORE, IGNORE};
            suffix = "CC";
            description = "unsigned lower";
            break;
        case 0b0100:
            flags = {IGNORE, SET, IGNORE, IGNORE};
            suffix = "MI";
            description = "negative";
            break;
        case 0b0101:
            flags = {IGNORE, CLEAR, IGNORE, IGNORE};
            suffix = "PL";
            description = "positive or zero";
            break;
        case 0b0110:
            flags = {IGNORE, IGNORE, SET, IGNORE};
            suffix = "VS";
            description = "overflow";
            break;
        case 0b0111:
            flags = {IGNORE, CLEAR, IGNORE, IGNORE};
            suffix = "VC";
            description = "no overflow";
            break;
        case 0b1000:
            flags = {SET, IGNORE, IGNORE, CLEAR};
            suffix = "HI";
            description = "unsigned higher";
            break;
        case 0b1001:
            flags = {CLEAR_OR, IGNORE, IGNORE, SET_OR};
            suffix = "LS";
            description = "unsigned lower or same";
            break;
        case 0b1010:
            flags = {IGNORE, EQUAL, EQUAL, IGNORE};
            suffix = "GE";
            description = "greater or equal";
            break;
        case 0b1011:
            flags = {IGNORE, NOT_EQUAL, NOT_EQUAL, IGNORE};
            suffix = "LT";
            description = "less than";
            break;
        case 0b1100:
            flags = {IGNORE, EQUAL, EQUAL, CLEAR};
            suffix = "GT";
            description = "greater than";
            break;
        case 0b1101:
            flags = {IGNORE, NOT_EQUAL, NOT_EQUAL, SET_OR};
            suffix = "LE";
            description = "less than or equal";
            break;
        case 0b1110:
            flags = {IGNORE, IGNORE, IGNORE, IGNORE};
            suffix = "AL";
            description = "always";
            break;
        default:
            assert(false);

    }

}

std::ostream& operator << ( std::ostream& outs, const Condition &c ){
    return outs << c.description;
}
