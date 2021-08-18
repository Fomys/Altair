#ifndef ALTAIR_VM_PROCESSOR_H
#define ALTAIR_VM_PROCESSOR_H

#include <malloc.h>

#include <base/vm.h>

#include "instruction.h"

enum ArProcessorStatus {
    AR_PROCESSOR_STATUS_INIT,
    AR_PROCESSOR_STATUS_FETCH,
    AR_PROCESSOR_STATUS_DECODE,
    AR_PROCESSOR_STATUS_STALL,
};

enum ArPRocessorMode {
    TWO_WAYS_DECODE,
    FOUR_WAYS_DECODE,
};

typedef struct ArProcessor_T {
    uint8_t dsram[AR_PROCESSOR_DSRAM_SIZE];
    uint8_t isram[AR_PROCESSOR_ISRAM_SIZE];
    uint8_t cache[AR_PROCESSOR_CACHE_SIZE];
    uint64_t ireg[AR_PROCESSOR_IREG_COUNT];

    uint8_t vreg[AR_PROCESSOR_VREG_COUNT*16];
    float * vfreg;
    double * vdreg;
    uint32_t * vireg;

    uint16_t pc;
    uint16_t br;
    uint16_t lr;

    enum ArPRocessorMode mode;

    enum ArProcessorStatus status;
    struct ArInstruction_T current_instructions[4];
} ArProcessor_T;



ArResult processor_alloc(struct ArProcessor_T ** processor);
ArResult processor_initialize(struct ArProcessor_T * processor);

ArResult processor_cycle(struct ArProcessor_T* processor);
ArResult processor_fetch(struct ArProcessor_T* processor);

void processor_free(struct ArProcessor_T * processor);

#endif //ALTAIR_VM_PROCESSOR_H
