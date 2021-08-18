#ifndef ALTAIR_VM_VIRTUAL_MACHINE_H
#define ALTAIR_VM_VIRTUAL_MACHINE_H

#include <assert.h>
#include <malloc.h>

#include <base/vm.h>

#include "processor.h"
#include "physical_memory.h"

typedef struct ArVirtualMachine_T {
    uint8_t processors_count;
    struct ArProcessor_T ** processors;

    struct ArPhysicalMemory_T * ram;
    struct ArPhysicalMemory_T * rom;
} ArVirtualMachine_T;

ArResult virtual_machine_alloc(struct ArVirtualMachine_T** virtual_machine);
ArResult virtual_machine_initialize(struct ArVirtualMachine_T* virtual_machine);

ArResult virtual_machine_attach_processor(struct ArVirtualMachine_T* virtual_machine, struct ArProcessor_T* processor);

void virtual_machine_forget_memory(struct ArVirtualMachine_T* virtual_machine, struct ArPhysicalMemory_T* memory);
void virtual_machine_forget_processor(struct ArVirtualMachine_T* virtual_machine, struct ArProcessor_T* processor);
void virtual_machine_free(struct ArVirtualMachine_T* virtual_machine);

#endif //ALTAIR_VM_VIRTUAL_MACHINE_H
