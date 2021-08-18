#include <string.h>
#include "processor.h"

ArResult processor_alloc(struct ArProcessor_T ** processor) {
    *processor = malloc(sizeof(struct ArProcessor_T));
    if(*processor == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }
    return AR_SUCCESS;
}

ArResult processor_initialize(struct ArProcessor_T * processor) {
    processor->status = AR_PROCESSOR_STATUS_INIT;
    processor->mode = FOUR_WAYS_DECODE;
    processor->vfreg = (float *) &processor->vreg;
    processor->vdreg = (double *) &processor->vreg;
    processor->vireg = (uint32_t *) &processor->vreg;
    return AR_SUCCESS;
}

ArResult processor_cycle(struct ArProcessor_T* processor) {
    if(processor->status == AR_PROCESSOR_STATUS_INIT) {
        return processor_fetch(processor);
    } else if (processor->status == AR_PROCESSOR_STATUS_FETCH) {

    }
    return AR_SUCCESS;
}


ArResult processor_fetch(struct ArProcessor_T* processor) {
    if(processor->mode == TWO_WAYS_DECODE) {
        uint32_t raw1;
        uint32_t raw2;
        memcpy(&raw1, &processor->isram[processor->pc * 4], sizeof(uint32_t));
        memcpy(&raw2, &processor->isram[(processor->pc + 1) * 4], sizeof(uint32_t));
        processor->current_instructions[0] = instruction_decode(raw1);
        processor->current_instructions[0].unit = instruction_get_unit(processor->current_instructions[0].opcode, 0);
        processor->current_instructions[1] = instruction_decode(raw2);
        processor->current_instructions[1].unit = instruction_get_unit(processor->current_instructions[1].opcode, 1);
    } else if (processor->mode == FOUR_WAYS_DECODE) {
        uint32_t raw1;
        uint32_t raw2;
        uint32_t raw3;
        uint32_t raw4;
        memcpy(&raw1, &processor->isram[processor->pc * 4], sizeof(uint32_t));
        memcpy(&raw2, &processor->isram[(processor->pc + 1) * 4], sizeof(uint32_t));
        memcpy(&raw3, &processor->isram[(processor->pc + 2) * 4], sizeof(uint32_t));
        memcpy(&raw4, &processor->isram[(processor->pc + 3) * 4], sizeof(uint32_t));
        printf("Raw = 0x%X 0x%X 0x%X 0x%X\n", raw1, raw2, raw3, raw4);
        processor->current_instructions[0] = instruction_decode(raw1);
        processor->current_instructions[0].unit = instruction_get_unit(processor->current_instructions[0].opcode, 0);
        processor->current_instructions[1] = instruction_decode(raw2);
        processor->current_instructions[1].unit = instruction_get_unit(processor->current_instructions[1].opcode, 1);
        processor->current_instructions[2] = instruction_decode(raw3);
        processor->current_instructions[2].unit = instruction_get_unit(processor->current_instructions[2].opcode, 2);
        processor->current_instructions[3] = instruction_decode(raw4);
        processor->current_instructions[3].unit = instruction_get_unit(processor->current_instructions[3].opcode, 3);
    }
    processor->status = AR_PROCESSOR_STATUS_FETCH;
    printf("Instructions = ");
    print_instruction(&processor->current_instructions[0]);
    printf(", ");
    print_instruction(&processor->current_instructions[1]);
    printf(", ");
    print_instruction(&processor->current_instructions[2]);
    printf(", ");
    print_instruction(&processor->current_instructions[3]);
    printf("\n");
    return AR_SUCCESS;
}

void processor_free(struct ArProcessor_T * processor) {

}