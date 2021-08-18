#ifndef ALTAIR_VM_INSTRUCTION_H
#define ALTAIR_VM_INSTRUCTION_H

#include <base/vm.h>

#define BITS(raw, index, size) (((raw) >> (index)) & ((1u << (size)) - 1))

struct ArInstructionParameters {
    uint8_t size;
    uint16_t small_immediate;
    uint16_t medium_immediate;
    uint32_t long_immediate;
    uint8_t reg_a;
    uint8_t reg_b;
    uint8_t reg_c;
    uint8_t id_1;
    uint8_t id_2;
};

enum ArUnit {
    AR_PROCESSOR_UNIT_ALU1 = 0,
    AR_PROCESSOR_UNIT_ALU2 = 1,
    AR_PROCESSOR_UNIT_ALU3 = 2,
    AR_PROCESSOR_UNIT_ALU4 = 3,
    AR_PROCESSOR_UNIT_CMP = 4,
    AR_PROCESSOR_UNIT_VFPU = 5,
    AR_PROCESSOR_UNIT_DMA = 6,
    AR_PROCESSOR_UNIT_LSU1 = 7,
    AR_PROCESSOR_UNIT_LSU2 = 8,
    AR_PROCESSOR_UNIT_UNKNOWN,
};


typedef struct ArInstruction_T {
    enum ArOpcode opcode;
    enum ArUnit unit;
    uint8_t swt;
    struct ArInstructionParameters parameters;
} ArInstruction_T;

struct ArInstruction_T instruction_decode(uint32_t raw, uint8_t instruction_id);

void instruction_print(struct ArInstruction_T * instruction);
void register_print(uint8_t reg);
void vregister_print(uint8_t reg);
void viregister_print(uint8_t reg, uint8_t id);
void unit_print(enum ArUnit unit);

#endif //ALTAIR_VM_INSTRUCTION_H
