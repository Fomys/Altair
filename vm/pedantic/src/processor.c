#include "processor.h"

ArResult pending_result_alloc(struct ArPendingResult ** result) {
    *result = malloc(sizeof(struct ArPendingResult));
    if(*result == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }
    return AR_SUCCESS;
}

ArResult pending_result_initialize(struct ArPendingResult * result) {
    result->next = NULL;
    result->delay = 255;
    return AR_SUCCESS;
}

void pending_result_free(struct ArPendingResult * result) {
    free(result->result);
    free(result);
}

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
    processor->vfreg = (struct ArVecFloat *) &processor->vreg;
    processor->vdreg = (struct ArVecDouble *) &processor->vreg;
    processor->vireg = (struct ArVecInt *) &processor->vreg;
    return AR_SUCCESS;
}

ArResult processor_pending_result_cycle(struct ArProcessor_T * processor) {
    struct ArPendingResult * next_pending = processor->pending_results;
    struct ArPendingResult ** prev_pending = &processor->pending_results;

    while(next_pending != NULL) {
        next_pending->delay--;

        if(next_pending->delay == 0) {
            memcpy(next_pending->destination, next_pending->result, next_pending->result_size);
            (*prev_pending) = next_pending->next;
            struct ArPendingResult *next = next_pending->next;
            pending_result_free(next_pending);
            next_pending = next;
        } else {
            next_pending = next_pending->next;
            prev_pending = &next_pending->next;
        }

    }

    return AR_SUCCESS;
}

ArResult processor_cycle(struct ArProcessor_T* processor) {
    ArResult result;
    processor_print(processor);

    result = processor_pending_result_cycle(processor);
    if(result != AR_SUCCESS) {
        return result;
    }

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
    ArResult result;
    uint8_t used_units[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(processor->current_instructions[0].opcode != AR_OPCODE_NOP) {
        used_units[processor->current_instructions[0].unit] = 1;
    }
    if(processor->current_instructions[1].opcode != AR_OPCODE_NOP) {
        if(used_units[processor->current_instructions[1].unit]) {
            return AR_ERROR_ILLEGAL_INSTRUCTION;
        }
        used_units[processor->current_instructions[1].unit] = 1;
    }
    result = processor_execute_instruction(processor, &processor->current_instructions[0]);
    if(result != AR_SUCCESS) {
        return result;
    }
    result = processor_execute_instruction(processor, &processor->current_instructions[1]);
    if(result != AR_SUCCESS) {
        return result;
    }
    if(processor->current_instructions[3].swt) {
        if(processor->current_instructions[2].opcode != AR_OPCODE_NOP) {
            if(used_units[processor->current_instructions[2].unit]) {
                return AR_ERROR_ILLEGAL_INSTRUCTION;
            }
            used_units[processor->current_instructions[2].unit] = 1;
        }
        if(processor->current_instructions[3].opcode != AR_OPCODE_NOP) {
            if(used_units[processor->current_instructions[3].unit]) {
                return AR_ERROR_ILLEGAL_INSTRUCTION;
            }
            used_units[processor->current_instructions[3].unit] = 1;
        }
        result = processor_execute_instruction(processor, &processor->current_instructions[2]);
        if(result != AR_SUCCESS) {
            return result;
        }
        result = processor_execute_instruction(processor, &processor->current_instructions[3]);
        if(result != AR_SUCCESS) {
            return result;
        }
    }
    return AR_SUCCESS;
}

ArResult processor_execute_instruction(struct ArProcessor_T* processor, struct ArInstruction_T * instruction) {
    if(instruction->opcode == AR_OPCODE_NOP) {
        return AR_SUCCESS;
    }
    struct ArPendingResult *next = processor->pending_results;
    pending_result_alloc(&processor->pending_results);
    pending_result_initialize(processor->pending_results);
    processor->pending_results->next = next;
    switch (instruction->opcode) {
        // TODO: Rajouter toutes les instructions
        case AR_OPCODE_ADD:
            return execute_add(processor, instruction, processor->pending_results);
        case AR_OPCODE_MOVEI:
            return execute_movei(processor, instruction, processor->pending_results);
        default:
            return AR_ERROR_ILLEGAL_INSTRUCTION;
    }
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
    printf("\tRegistres généraux: \n");
    for(uint8_t reg_id = 0; reg_id < 16; reg_id++) {
        printf("\t\t");
        register_print(reg_id*4);
        printf(": 0x%016lX\t", processor->ireg[reg_id*4]);
        register_print(reg_id*4+1);
        printf(": 0x%016lX\t", processor->ireg[reg_id*4+1]);
        register_print(reg_id*4+2);
        printf(": 0x%016lX\t", processor->ireg[reg_id*4+2]);
        register_print(reg_id*4+3);
        printf(": 0x%016lX\n", processor->ireg[reg_id*4+3]);
    }
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