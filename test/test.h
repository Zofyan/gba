//
// Created by Sofyan on 27/08/2022.
//

#ifndef GBETEST_TEST_H
#define GBETEST_TEST_H

#include <cstdint>
union mul_instruction_int {
    struct mul_instruction {
        uint32_t rm: 4;
        uint32_t mask1: 4;
        uint32_t rs: 4;
        uint32_t rn: 4;
        uint32_t rd: 4;
        uint32_t s: 1;
        uint32_t subcode: 4;
        uint32_t mask0: 3;
        uint32_t cond: 4;
    } mul_instruction_t;
    uint32_t mul_instruction_int_t;
};
union alu_instruction_int_i_is_0 {
    struct alu_instruction_i_is_0 {
        uint32_t rm: 4;
        uint32_t r: 1;
        uint32_t shift_type: 2;
        uint32_t shift_amount_register: 5;
        uint32_t rd: 4;
        uint32_t rn: 4;
        uint32_t s: 1;
        uint32_t subcode: 4;
        uint32_t immediate_operant: 1;
        uint32_t mask0: 2;
        uint32_t cond: 4;
    } alu_instruction_i_is_0_t;
    uint32_t alu_instruction_int_i_is_0_t;
};
union alu_instruction_int_i_is_1 {
    struct alu_instruction_i_is_1 {
        uint32_t nn: 8;
        uint32_t ror_shift: 4;
        uint32_t rd: 4;
        uint32_t rn: 4;
        uint32_t s: 1;
        uint32_t subcode: 4;
        uint32_t immediate_operant: 1;
        uint32_t mask0: 2;
        uint32_t cond: 4;
    } alu_instruction_i_is_1_t;
    uint32_t alu_instruction_int_i_is_1_t;
};
#endif //GBETEST_TEST_H
