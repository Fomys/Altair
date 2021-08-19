#ifndef ALTAIR_VM_EXECUTE_OPCODE_H
#define ALTAIR_VM_EXECUTE_OPCODE_H

#include <base/vm.h>
#include "instruction.h"
#include "processor.h"

ArResult execute_add(struct ArProcessor_T * processor, struct ArInstruction_T * instruction, struct ArPendingResult * pending);
ArResult execute_movei(struct ArProcessor_T * processor, struct ArInstruction_T * instruction, struct ArPendingResult * pending);

#endif //ALTAIR_VM_EXECUTE_OPCODE_H
