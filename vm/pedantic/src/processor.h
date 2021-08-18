#ifndef ALTAIR_VM_PROCESSOR_H
#define ALTAIR_VM_PROCESSOR_H

#include <malloc.h>

#include <base/vm.h>

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
} ArProcessor_T;

ArResult processor_alloc(struct ArProcessor_T ** processor);
ArResult processor_initialize(struct ArProcessor_T * processor);

ArResult processor_cycle(struct ArProcessor_T* processor);

void processor_free(struct ArProcessor_T * processor);

#endif //ALTAIR_VM_PROCESSOR_H
