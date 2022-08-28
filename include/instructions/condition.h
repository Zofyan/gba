//
// Created by Sofyan on 26/08/2022.
//

#ifndef GBE_CONDITION_H
#define GBE_CONDITION_H


#include <cstdint>
#include <string>
#include <sstream>

enum conditions{
    EQ = 0,
    NE = 1,
    CS = 2,
    CC = 3,
    MI = 4,
    PL = 5,
    VS = 6,
    VC = 7,
    HI = 8,
    LS = 9,
    GE = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    AL = 14
};

enum flag_status{
    CLEAR,
    SET,
    IGNORE,
    CLEAR_OR,
    SET_OR,
    EQUAL,
    NOT_EQUAL
};

typedef struct flags {
    flag_status c;
    flag_status n;
    flag_status v;
    flag_status z;
} flags_t;

class Condition {
private:
    uint8_t code{};
    std::string suffix;
public:
    std::string description;
    explicit Condition(uint8_t code);

    flags_t flags{};
};

std::ostream& operator << ( std::ostream& outs, const Condition &c );

#endif //GBE_CONDITION_H
