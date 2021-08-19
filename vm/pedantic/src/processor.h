#ifndef ALTAIR_VM_PROCESSOR_H
#define ALTAIR_VM_PROCESSOR_H

#include <malloc.h>
#include <string.h>

#include <base/vm.h>

#include "execute_opcode.h"
#include "instruction.h"

struct ArVecFloat {
    float x;
    float y;
    float z;
    float t;
};

struct ArVecDouble {
    double x;
    double y;
};

struct ArVecInt {
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t t;
};

struct ArPendingResult {
    struct ArPendingResult* next;
    uint8_t * result;
    uint8_t * destination;
    uint8_t result_size;
    uint8_t delay;
};

typedef struct ArProcessor_T {
    uint8_t dsram[AR_PROCESSOR_DSRAM_SIZE];
    uint8_t isram[AR_PROCESSOR_ISRAM_SIZE];
    uint8_t cache[AR_PROCESSOR_CACHE_SIZE];

    uint64_t ireg[AR_PROCESSOR_IREG_COUNT];

    uint8_t vreg[AR_PROCESSOR_VREG_COUNT*16];
    struct ArVecFloat * vfreg;
    struct ArVecDouble * vdreg;
    struct ArVecInt * vireg;

    uint16_t pc;

    uint32_t current_raw[4];
    struct ArInstruction_T current_instructions[4];
    struct ArPendingResult * pending_results;
} ArProcessor_T;

ArResult pending_result_alloc(struct ArPendingResult ** result);
ArResult processor_alloc(struct ArProcessor_T ** processor);

ArResult pending_result_initialize(struct ArPendingResult * result);
ArResult processor_initialize(struct ArProcessor_T * processor);

void processor_print(struct ArProcessor_T* processor);

ArResult processor_cycle(struct ArProcessor_T* processor);
ArResult processor_pending_result_cycle(struct ArProcessor_T * processor);
ArResult processor_fetch(struct ArProcessor_T* processor);
ArResult processor_decode(struct ArProcessor_T* processor);
ArResult processor_execute(struct ArProcessor_T* processor);
ArResult processor_execute_instruction(struct ArProcessor_T* processor, struct ArInstruction_T * instruction);

void pending_result_free(struct ArPendingResult * result);
void processor_free(struct ArProcessor_T * processor);

#endif //ALTAIR_VM_PROCESSOR_H
