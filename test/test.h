//
// Created by Sofyan on 27/08/2022.
//

#ifndef GBETEST_TEST_H
#define GBETEST_TEST_H

#include <cstdint>
union mul_instruction_int {
    struct mul_instruction {
        uint32_t cond: 4;
        uint32_t mask0: 6;
        uint32_t a: 1;
        uint32_t s: 1;
        uint32_t rd: 4;
        uint32_t rn: 4;
        uint32_t rs: 4;
        uint32_t mask1: 4;
        uint32_t rm: 4;
    } mul_instruction_t;
    uint32_t mul_instruction_int_t;
};
#endif //GBETEST_TEST_H
