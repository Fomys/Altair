#include "physical_memory.h"

ArResult physical_memory_alloc(struct ArPhysicalMemory_T ** memory) {
    *memory = malloc(sizeof(struct ArPhysicalMemory_T));
    if(*memory == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }

    return AR_SUCCESS;
}

ArResult physical_memory_initialize(struct ArPhysicalMemory_T * memory, const ArPhysicalMemoryCreateInfo * info) {
    memory->size = info->size;
    memory->memory = info->pMemory;

    return AR_SUCCESS;
}

void physical_memory_forget_memory(struct ArPhysicalMemory_T* memory) {
    memory->memory = NULL;
}

void physical_memory_free(struct ArPhysicalMemory_T* memory) {
    free(memory->memory);
    free(memory);
}