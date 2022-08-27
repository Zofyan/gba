//
// Created by Sofyan on 26/08/2022.
//

#ifndef GBE_CONDITION_H
#define GBE_CONDITION_H


#include <cstdint>
#include <string>
#include <sstream>

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
    flags_t flags{};
public:
    std::string description;
    explicit Condition(uint8_t code);
};

std::ostream& operator << ( std::ostream& outs, const Condition &c );

#endif //GBE_CONDITION_H
