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
    processor->current_raw[0] = 0xA;
    processor->current_raw[1] = 0xA;
    processor->current_raw[2] = 0xA;
    processor->current_raw[3] = 0xA;
    processor->current_instructions[0] = (struct ArInstruction_T) {.opcode = AR_OPCODE_NOP};
    processor->current_instructions[1] = (struct ArInstruction_T) {.opcode = AR_OPCODE_NOP};
    processor->current_instructions[2] = (struct ArInstruction_T) {.opcode = AR_OPCODE_NOP};
    processor->current_instructions[3] = (struct ArInstruction_T) {.opcode = AR_OPCODE_NOP};
    processor->vfreg = (float *) &processor->vreg;
    processor->vdreg = (double *) &processor->vreg;
    processor->vireg = (uint32_t *) &processor->vreg;
    return AR_SUCCESS;
}

ArResult processor_cycle(struct ArProcessor_T* processor) {
    ArResult result;
    processor_print(processor);
    getchar();

    result = processor_execute(processor);
    if(result != AR_SUCCESS) {
        return result;
    }

    result = processor_decode(processor);
    if(result != AR_SUCCESS) {
        return result;
    }

    result = processor_fetch(processor);
    if(result != AR_SUCCESS) {
        return result;
    }


    return AR_SUCCESS;
}

ArResult processor_execute(struct ArProcessor_T* processor) {

    return AR_SUCCESS;
}

void processor_print(struct ArProcessor_T* processor) {
    printf("Processor status:\n");
    printf("\tpc: %hu\n", processor->pc);
    printf("\tcurrent_raw: 0x%08X, 0x%08X, 0x%08X, 0x%08X\n", processor->current_raw[0], processor->current_raw[1], processor->current_raw[2], processor->current_raw[3]);
    printf("\tcurrent_instructions: ");
    instruction_print(&processor->current_instructions[0]);
    printf(", ");
    instruction_print(&processor->current_instructions[1]);
    printf(", ");
    instruction_print(&processor->current_instructions[2]);
    printf(", ");
    instruction_print(&processor->current_instructions[3]);
    printf("\n");
}

ArResult processor_fetch(struct ArProcessor_T* processor) {
    processor->current_raw[0] = 0xA;
    processor->current_raw[1] = 0xA;
    processor->current_raw[2] = 0xA;
    processor->current_raw[3] = 0xA;
    if (((processor->pc + 1) * 4) < AR_PROCESSOR_ISRAM_SIZE) {
        memcpy(&processor->current_raw[0], &processor->isram[processor->pc * 4], sizeof(uint32_t));
        processor->pc++;
        memcpy(&processor->current_raw[1], &processor->isram[processor->pc * 4], sizeof(uint32_t));
        processor->pc++;
    }
    // On n'est pas au bout de la ISRAM et on a une instruction swt
    if (((processor->pc + 3) * 4) < AR_PROCESSOR_ISRAM_SIZE && BITS(processor->isram[(processor->pc + 1) * 4], 0, 4) == 0b1100) {
        memcpy(&processor->current_raw[2], &processor->isram[processor->pc * 4], sizeof(uint32_t));
        processor->pc++;
        memcpy(&processor->current_raw[3], &processor->isram[(processor->pc + 1) * 4], sizeof(uint32_t));
        processor->pc++;
    }
    return AR_SUCCESS;
}

ArResult processor_decode(struct ArProcessor_T* processor) {
    processor->current_instructions[0] = instruction_decode(processor->current_raw[0], 0);
    processor->current_instructions[1] = instruction_decode(processor->current_raw[1], 1);
    processor->current_instructions[2] = instruction_decode(processor->current_raw[2], 2);
    processor->current_instructions[3] = instruction_decode(processor->current_raw[3], 3);
    return AR_SUCCESS;
}

void processor_free(struct ArProcessor_T * processor) {

}