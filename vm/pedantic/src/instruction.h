#ifndef ALTAIR_VM_INSTRUCTION_H
#define ALTAIR_VM_INSTRUCTION_H

#include <base/vm.h>

#define BITS(raw, index, size) (((raw) >> (index)) & ((1u << (size)) - 1))

struct ArInstructionParameters {
    uint8_t size;
    uint32_t immediate;
    uint8_t reg_a;
    uint8_t reg_b;
    uint8_t reg_c;
    uint8_t id_1;
    uint8_t id_2;
};

enum ArUnit {
    AR_PROCESSOR_UNIT_UNKNOWN,
    AR_PROCESSOR_UNIT_CMP,
    AR_PROCESSOR_UNIT_VFPU,
    AR_PROCESSOR_UNIT_DMA,
    AR_PROCESSOR_UNIT_ALU1,
    AR_PROCESSOR_UNIT_ALU2,
    AR_PROCESSOR_UNIT_ALU3,
    AR_PROCESSOR_UNIT_ALU4,
    AR_PROCESSOR_UNIT_LSU1,
    AR_PROCESSOR_UNIT_LSU2,
};


typedef struct ArInstruction_T {
    enum ArOpcode opcode;
    enum ArUnit unit;
    struct ArInstructionParameters parameters;
} ArInstruction_T;

struct ArInstruction_T instruction_decode(uint32_t raw);

void instruction_decode_00_00(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_00_01(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_00_10(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_00_11(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_01_00(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_01_01(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_01_10(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_01_11(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_10_00(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_10_01(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_10_10(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_10_11(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_11_00(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_11_01(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_11_10(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);
void instruction_decode_11_11(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id);

void print_instruction(struct ArInstruction_T * instructionT);

#endif //ALTAIR_VM_INSTRUCTION_H
