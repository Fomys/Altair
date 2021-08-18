#include <string.h>
#include "vm.h"

ArResult arCreateVirtualMachine(ArVirtualMachine* virtual_machine, const ArVirtualMachineCreateInfo* info) {
    ArResult result;

    result = virtual_machine_alloc(virtual_machine);
    if(result != AR_SUCCESS) {
        return result;
    }

    result = virtual_machine_initialize(*virtual_machine);
    if(result != AR_SUCCESS) {
        return result;
    }

    return AR_SUCCESS;
}

ArResult arCreatePhysicalMemory(
        ArVirtualMachine virtual_machine,
        const ArPhysicalMemoryCreateInfo* info,
        ArPhysicalMemory* memory) {
    ArResult result;

    result = physical_memory_alloc(memory);
    if(result != AR_SUCCESS) {
        return result;
    }

    if(info->role == AR_PHYSICAL_MEMORY_ROLE_RAM) {
        if(virtual_machine->ram != NULL) {
            return AR_ERROR_RAM_ALREADY_INITIALIZED;
        }
        virtual_machine->ram = *memory;
    } else if(info->role == AR_PHYSICAL_MEMORY_ROLE_ROM) {
        if(virtual_machine->rom != NULL) {
            return AR_ERROR_ROM_ALREADY_INITIALIZED;
        }
        virtual_machine->rom = *memory;
    } else {
        return AR_ERROR_UNKNOWN_MEMORY_ROLE;
    }

    result = physical_memory_initialize(*memory, info);
    if(result != AR_SUCCESS) {
        return result;
    }

    return AR_SUCCESS;
}

ArResult arCreateProcessor(
        ArVirtualMachine virtual_machine,
        const ArProcessorCreateInfo* info,
        ArProcessor* processor) {
    ArResult result;
    result = processor_alloc(processor);
    if(result != AR_SUCCESS) {
        return result;
    }

    result = processor_initialize(*processor);
    if(result != AR_SUCCESS) {
        return result;
    }

    memcpy((*processor)->isram, info->pBootCode, info->bootCodeSize * sizeof(uint32_t));
    memcpy(virtual_machine->rom->memory, info->pBootCode, info->bootCodeSize * sizeof(uint32_t));

    result = virtual_machine_attach_processor(virtual_machine, *processor);
    if(result != AR_SUCCESS) {
        return result;
    }

    return AR_SUCCESS;
}


ArPhysicalMemory* getMemoryByRole(
        ArVirtualMachine virtual_machine,
        ArPhysicalMemoryRole role) {
    printf("getMemoryByRole\n");
}

void arGetProcessorOperations(
        ArProcessor processor,
        ArOperation* output,
        size_t* count) {
    printf("arGetProcessorOperations\n");
}

void arGetProcessorMemoryInfo(
        ArProcessor processor,
        ArProcessorMemoryInfo* output) {
    output->dsram  = processor->dsram;
    output->isram  = processor->isram;
    output->cache  = processor->cache;
    output->ireg   = processor->ireg;
    output->vreg   = (uint64_t*) processor->vreg;
}

void arDestroyVirtualMachine(ArVirtualMachine virtual_machine) {
    virtual_machine_free(virtual_machine);
}

void arDestroyProcessor(
        ArVirtualMachine virtual_machine,
        ArProcessor processor) {
    virtual_machine_forget_processor(virtual_machine, processor);
    processor_free(processor);
}

void arDestroyPhysicalMemory(
        ArVirtualMachine virtual_machine,
        ArPhysicalMemory memory) {
    virtual_machine_forget_memory(virtual_machine, memory);
    physical_memory_forget_memory(memory);
    physical_memory_free(memory);
}

ArResult arDecodeInstruction(ArProcessor processor){
    return AR_SUCCESS;
}

ArResult arExecuteInstruction(ArProcessor processor){
    return processor_cycle(processor);
}
