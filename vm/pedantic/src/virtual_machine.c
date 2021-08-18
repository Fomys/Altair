#include "virtual_machine.h"

ArResult virtual_machine_alloc(struct ArVirtualMachine_T** virtual_machine) {
    *virtual_machine = malloc(sizeof(struct ArVirtualMachine_T));
    if(*virtual_machine == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }

    return AR_SUCCESS;
}

ArResult virtual_machine_initialize(struct ArVirtualMachine_T* virtual_machine) {
    virtual_machine->processors_count = 0;
    virtual_machine->processors = NULL;
    virtual_machine->ram = NULL;
    virtual_machine->rom = NULL;

    return AR_SUCCESS;
}

ArResult virtual_machine_attach_processor(struct ArVirtualMachine_T* virtual_machine, struct ArProcessor_T* processor) {
    if(virtual_machine->processors_count > 255) {
        return AR_TOO_MANY_PROCESSORS;
    }
    struct ArProcessor_T **old_processors = virtual_machine->processors;
    virtual_machine->processors = realloc(virtual_machine->processors, sizeof(struct ArProcessor_T*) * (1 + virtual_machine->processors_count));
    if(virtual_machine->processors == NULL) {
        virtual_machine->processors = old_processors;
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }

    virtual_machine->processors[virtual_machine->processors_count] = processor;
    virtual_machine->processors_count++;
    return AR_SUCCESS;
}

void virtual_machine_forget_memory(struct ArVirtualMachine_T* virtual_machine, struct ArPhysicalMemory_T* memory) {
    if(virtual_machine->ram == memory) {
        virtual_machine->ram = NULL;
    } else if(virtual_machine->rom == memory) {
        virtual_machine->rom = NULL;
    } else {
        return;
    }
}

void virtual_machine_forget_processor(struct ArVirtualMachine_T* virtual_machine, struct ArProcessor_T* processor) {
    uint8_t proc_id;
    for(proc_id = 0; proc_id < virtual_machine->processors_count; proc_id++) {
        if (virtual_machine->processors[proc_id] == processor) {
            break;
        }
    }
    if(proc_id < virtual_machine->processors_count) {
        virtual_machine->processors_count --;
    }
    for(; proc_id < virtual_machine->processors_count; proc_id++) {
        virtual_machine->processors[proc_id] = virtual_machine->processors[proc_id+1];
    }
}

void virtual_machine_free(struct ArVirtualMachine_T* virtual_machine) {
    if(virtual_machine->ram != NULL) {
        physical_memory_free(virtual_machine->ram);
    }
    if(virtual_machine->rom != NULL) {
        physical_memory_free(virtual_machine->rom);
    }
    for(uint8_t proc_id = 0; proc_id < virtual_machine->processors_count; proc_id++) {
        processor_free(virtual_machine->processors[proc_id]);
    }
    free(virtual_machine->processors);
    free(virtual_machine);
}