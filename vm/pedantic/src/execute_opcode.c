#include "execute_opcode.h"

ArResult execute_add(struct ArProcessor_T * processor, struct ArInstruction_T * instruction, struct ArPendingResult * pending) {
    pending->delay = 3;
    pending->result_size = sizeof(uint64_t);
    pending->result = malloc(sizeof(uint64_t));
    if(pending->result == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }
    uint64_t mask;
    switch (instruction->parameters.size) {
        case 0b00:
            mask = 0x00000000000000FF;
            break;
        case 0b10:
            mask = 0x000000000000FFFF;
            break;
        case 0b01:
            mask = 0x00000000FFFFFFFF;
            break;
        case 0b11:
            mask = 0xFFFFFFFFFFFFFFFF;
            break;
        default:
            return AR_ERROR_ILLEGAL_INSTRUCTION;
    }
    uint64_t result = (
            (processor->ireg[instruction->parameters.reg_a] + processor->ireg[instruction->parameters.reg_b]) & mask);
    memcpy(pending->result, &result, sizeof(uint64_t));
    pending->destination = &processor->ireg[instruction->parameters.reg_c];
    return AR_SUCCESS;
}

ArResult execute_movei(struct ArProcessor_T * processor, struct ArInstruction_T * instruction, struct ArPendingResult * pending) {
    pending->delay = 3;
    pending->result_size = sizeof(uint32_t);
    pending->result = malloc(pending->result_size);
    if(pending->result == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }
    memcpy(pending->result, &instruction->parameters.long_immediate, pending->result_size);
    pending->destination = &processor->ireg[instruction->parameters.reg_a];
    return AR_SUCCESS;
}
