#ifndef ALTAIR_VM_PHYSICAL_MEMORY_H
#define ALTAIR_VM_PHYSICAL_MEMORY_H

#include <assert.h>
#include <malloc.h>

#include <base/vm.h>

typedef struct ArPhysicalMemory_T {
    uint8_t* memory;
    size_t size;
} ArPhysicalMemory_T;

ArResult physical_memory_alloc(struct ArPhysicalMemory_T ** memory);
ArResult physical_memory_initialize(struct ArPhysicalMemory_T * memory, const ArPhysicalMemoryCreateInfo * info);

void physical_memory_forget_memory(struct ArPhysicalMemory_T* memory);
void physical_memory_free(struct ArPhysicalMemory_T* memory);

#endif //ALTAIR_VM_PHYSICAL_MEMORY_H
