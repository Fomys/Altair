#ifndef ALTAIR_VM_INTERNAL_H_DEFINED
#define ALTAIR_VM_INTERNAL_H_DEFINED

#include <base/vm.h>
#include <stdio.h>

#include "virtual_machine.h"

ArPhysicalMemory* getMemoryByRole(ArVirtualMachine virtual_machine, ArPhysicalMemoryRole role);
ArResult arCreateVirtualMachine(ArVirtualMachine* virtual_machine, const ArVirtualMachineCreateInfo* info);
ArResult arCreateProcessor(ArVirtualMachine virtual_machine, const ArProcessorCreateInfo* info, ArProcessor* processor);
ArResult arCreatePhysicalMemory(ArVirtualMachine virtual_machine, const ArPhysicalMemoryCreateInfo* info, ArPhysicalMemory* memory);
ArPhysicalMemory* getMemoryByRole(ArVirtualMachine virtual_machine, ArPhysicalMemoryRole role);
void arGetProcessorOperations(ArProcessor processor, ArOperation* output, size_t* count);
void arGetProcessorMemoryInfo(ArProcessor processor, ArProcessorMemoryInfo* pOutput);
void arDestroyVirtualMachine(ArVirtualMachine virtualMachine);
void arDestroyProcessor(ArVirtualMachine virtualMachine, ArProcessor processor);
void arDestroyPhysicalMemory(ArVirtualMachine virtualMachine, ArPhysicalMemory memory);
ArResult arDecodeInstruction(ArProcessor processor);
ArResult arExecuteInstruction(ArProcessor processor);


#endif
