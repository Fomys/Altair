#include <stdio.h>
#include "instruction.h"


enum ArUnit instruction_decode_unit[4][4] = {
        AR_PROCESSOR_UNIT_CMP, AR_PROCESSOR_UNIT_DMA, AR_PROCESSOR_UNIT_ALU3, AR_PROCESSOR_UNIT_ALU4,
        AR_PROCESSOR_UNIT_LSU1, AR_PROCESSOR_UNIT_LSU2, AR_PROCESSOR_UNIT_LSU1, AR_PROCESSOR_UNIT_LSU2,
        AR_PROCESSOR_UNIT_ALU1, AR_PROCESSOR_UNIT_ALU2, AR_PROCESSOR_UNIT_ALU1, AR_PROCESSOR_UNIT_ALU2,
        AR_PROCESSOR_UNIT_VFPU, AR_PROCESSOR_UNIT_VFPU, AR_PROCESSOR_UNIT_VFPU, AR_PROCESSOR_UNIT_VFPU
};

enum ArUnit instruction_decode_unit_swt[8] = {
        AR_PROCESSOR_UNIT_ALU2,
        AR_PROCESSOR_UNIT_ALU2,
        AR_PROCESSOR_UNIT_ALU4,
        AR_PROCESSOR_UNIT_LSU2,
        AR_PROCESSOR_UNIT_VFPU,
        AR_PROCESSOR_UNIT_VFPU,
        AR_PROCESSOR_UNIT_VFPU,
        AR_PROCESSOR_UNIT_VFPU,
};

enum ArOpcode instruction_decode_opcodes[9][64] = {
        {
                AR_OPCODE_ADD, AR_OPCODE_ADDI,AR_OPCODE_NOP, AR_OPCODE_MOVEI,
                AR_OPCODE_SUB, AR_OPCODE_SUBI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_XOR, AR_OPCODE_XORI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_OR,AR_OPCODE_ORI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_AND, AR_OPCODE_ANDI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSL, AR_OPCODE_LSLI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_ASR, AR_OPCODE_ASRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSR,AR_OPCODE_LSRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_MULS, AR_OPCODE_MULSI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_MULU, AR_OPCODE_MULUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVS, AR_OPCODE_DIVSI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVU,AR_OPCODE_DIVUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_REMS,AR_OPCODE_REMSI, AR_OPCODE_MOVEINS, AR_OPCODE_MOVEI,
                AR_OPCODE_REMU, AR_OPCODE_REMUI, AR_OPCODE_MOVECYC, AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEFR,AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEIR,AR_OPCODE_MOVEI,
        },
        {
                AR_OPCODE_ADD, AR_OPCODE_ADDI,AR_OPCODE_NOP, AR_OPCODE_MOVEI,
                AR_OPCODE_SUB, AR_OPCODE_SUBI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_XOR, AR_OPCODE_XORI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_OR,AR_OPCODE_ORI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_AND, AR_OPCODE_ANDI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSL, AR_OPCODE_LSLI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_ASR, AR_OPCODE_ASRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSR,AR_OPCODE_LSRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_MULS, AR_OPCODE_MULSI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_MULU, AR_OPCODE_MULUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVS, AR_OPCODE_DIVSI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVU,AR_OPCODE_DIVUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_REMS,AR_OPCODE_REMSI, AR_OPCODE_MOVEINS, AR_OPCODE_MOVEI,
                AR_OPCODE_REMU, AR_OPCODE_REMUI, AR_OPCODE_MOVECYC, AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEFR,AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEIR,AR_OPCODE_MOVEI,
        },
        {
                AR_OPCODE_ADD, AR_OPCODE_ADDI,AR_OPCODE_NOP, AR_OPCODE_MOVEI,
                AR_OPCODE_SUB, AR_OPCODE_SUBI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_XOR, AR_OPCODE_XORI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_OR,AR_OPCODE_ORI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_AND, AR_OPCODE_ANDI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSL, AR_OPCODE_LSLI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_ASR, AR_OPCODE_ASRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSR,AR_OPCODE_LSRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_MULS, AR_OPCODE_MULSI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_MULU, AR_OPCODE_MULUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVS, AR_OPCODE_DIVSI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVU,AR_OPCODE_DIVUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_REMS,AR_OPCODE_REMSI, AR_OPCODE_MOVEINS, AR_OPCODE_MOVEI,
                AR_OPCODE_REMU, AR_OPCODE_REMUI, AR_OPCODE_MOVECYC, AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEFR,AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEIR,AR_OPCODE_MOVEI,
        },
        {
                AR_OPCODE_ADD, AR_OPCODE_ADDI,AR_OPCODE_NOP, AR_OPCODE_MOVEI,
                AR_OPCODE_SUB, AR_OPCODE_SUBI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_XOR, AR_OPCODE_XORI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_OR,AR_OPCODE_ORI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_AND, AR_OPCODE_ANDI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSL, AR_OPCODE_LSLI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_ASR, AR_OPCODE_ASRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_LSR,AR_OPCODE_LSRI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_MULS, AR_OPCODE_MULSI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_MULU, AR_OPCODE_MULUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVS, AR_OPCODE_DIVSI,AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,
                AR_OPCODE_DIVU,AR_OPCODE_DIVUI, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEI,

                AR_OPCODE_REMS,AR_OPCODE_REMSI, AR_OPCODE_MOVEINS, AR_OPCODE_MOVEI,
                AR_OPCODE_REMU, AR_OPCODE_REMUI, AR_OPCODE_MOVECYC, AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEFR,AR_OPCODE_MOVEI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_MOVEIR,AR_OPCODE_MOVEI,
        },
        {
                AR_OPCODE_CMP, AR_OPCODE_BNE, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_BEQ, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_BL,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_BLE, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,

                AR_OPCODE_FCMP,AR_OPCODE_BG,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_DCMP,AR_OPCODE_BGE, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_FCMPI, AR_OPCODE_BLS, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_DCMPI,AR_OPCODE_BLES,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,

                AR_OPCODE_ENDP, AR_OPCODE_BGS, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_RET,AR_OPCODE_BGES,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_INT,AR_OPCODE_BRA,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_RETI,AR_OPCODE_JUMP,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,

                AR_OPCODE_UNKNOWN, AR_OPCODE_JUMPBR,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN,AR_OPCODE_CALL,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_CALLBR,AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
                AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_CMPI,
        },
        {
                AR_OPCODE_FADD,AR_OPCODE_FMOVE, AR_OPCODE_FDIV,AR_OPCODE_DMOVEI,
                AR_OPCODE_FSUB,AR_OPCODE_VFMOVE,AR_OPCODE_FSQRT, AR_OPCODE_DADD,
                AR_OPCODE_FMUL,AR_OPCODE_FMOVEI,AR_OPCODE_UNKNOWN, AR_OPCODE_DSUB,
                AR_OPCODE_FMULADD, AR_OPCODE_VFMOVEI, AR_OPCODE_UNKNOWN, AR_OPCODE_DMUL,

                AR_OPCODE_VFADD, AR_OPCODE_FNEG,AR_OPCODE_FATAN, AR_OPCODE_DABS,
                AR_OPCODE_VFSUB, AR_OPCODE_FABS,AR_OPCODE_FATAN2,AR_OPCODE_DNEG,
                AR_OPCODE_VFMUL, AR_OPCODE_VFNEG, AR_OPCODE_FEXP,AR_OPCODE_DMIN,
                AR_OPCODE_VFMULADD, AR_OPCODE_VFABS, AR_OPCODE_UNKNOWN, AR_OPCODE_DMAX,

                AR_OPCODE_VFADDS, AR_OPCODE_VFTOH, AR_OPCODE_FSUM,AR_OPCODE_DDIV,
                AR_OPCODE_VFSUBS, AR_OPCODE_VHTOF, AR_OPCODE_FIPR,AR_OPCODE_DSQRT,
                AR_OPCODE_VFMULS, AR_OPCODE_VFTOI,AR_OPCODE_FSIN,AR_OPCODE_DSIN,
                AR_OPCODE_VFMULADDS, AR_OPCODE_VITOF, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_FMULSUB, AR_OPCODE_VFTOD, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_VFMULSUB, AR_OPCODE_VDTOF, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_VFMULSUBS, AR_OPCODE_FMIN,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_VFSHUFFLE, AR_OPCODE_FMAX,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
                AR_OPCODE_LDDMA,   AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_STDMA,   AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_LDDMACL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_STDMACL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,

                AR_OPCODE_DMAI,     AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_UNKNOWN,  AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_UNKNOWN,  AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,
                AR_OPCODE_UNKNOWN,  AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_SWT,

                AR_OPCODE_LDDMAI,   AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STDMAI,   AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDDMACLI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STDMACLI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_DMAII,    AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_UNKNOWN,  AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_UNKNOWN,  AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_WAIT,     AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
                AR_OPCODE_LDM, AR_OPCODE_LDMIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STM, AR_OPCODE_STMIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDC, AR_OPCODE_LDCIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STC, AR_OPCODE_STCIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMV,AR_OPCODE_LDMVIL,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMV,AR_OPCODE_STMVIL,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCV,AR_OPCODE_LDCVIL,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCV, AR_OPCODE_STCVIL,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMI, AR_OPCODE_PREFETCHI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMI, AR_OPCODE_FLUSHI,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCI, AR_OPCODE_PREFETCH, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCI,AR_OPCODE_FLUSH, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMVI,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
                AR_OPCODE_LDM, AR_OPCODE_LDMIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STM, AR_OPCODE_STMIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDC, AR_OPCODE_LDCIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STC, AR_OPCODE_STCIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMV, AR_OPCODE_LDMVIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMV, AR_OPCODE_STMVIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCV, AR_OPCODE_LDCVIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCV, AR_OPCODE_STCVIL, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMI, AR_OPCODE_PREFETCHI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMI, AR_OPCODE_FLUSHI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCI, AR_OPCODE_PREFETCH, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCI,AR_OPCODE_FLUSH, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,

                AR_OPCODE_LDMVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STMVI,AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_LDCVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
                AR_OPCODE_STCVI, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
};

enum ArOpcode instruction_decode_opcodes_swt[8][16] = {
        {
            AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP,
            AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP,
            AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP,
            AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP, AR_OPCODE_NOP,
        },
        {
            AR_OPCODE_ADD, AR_OPCODE_SUB, AR_OPCODE_XOR, AR_OPCODE_OR,
            AR_OPCODE_AND, AR_OPCODE_LSL, AR_OPCODE_ASR, AR_OPCODE_LSR,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
            AR_OPCODE_ADD, AR_OPCODE_SUB, AR_OPCODE_XOR, AR_OPCODE_OR,
            AR_OPCODE_AND, AR_OPCODE_LSL, AR_OPCODE_ASR, AR_OPCODE_LSR,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
            AR_OPCODE_LDM, AR_OPCODE_STM, AR_OPCODE_LDC, AR_OPCODE_STC,
            AR_OPCODE_LDMV, AR_OPCODE_STMV, AR_OPCODE_LDCV, AR_OPCODE_STCV,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_VFADD, AR_OPCODE_FSUB, AR_OPCODE_FMUL, AR_OPCODE_FMULADD,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
        },
        {
            AR_OPCODE_UNKNOWN, AR_OPCODE_VFMOVE, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_VFNEG, AR_OPCODE_VFABS,
            AR_OPCODE_VFTOH, AR_OPCODE_VHTOF, AR_OPCODE_VFTOI, AR_OPCODE_VITOF,
            AR_OPCODE_VFTOD, AR_OPCODE_VDTOF, AR_OPCODE_FMIN, AR_OPCODE_FMAX,
        },
        {
            AR_OPCODE_UNKNOWN, AR_OPCODE_DADD, AR_OPCODE_DSUB, AR_OPCODE_DMUL,
            AR_OPCODE_DABS, AR_OPCODE_DNEG, AR_OPCODE_DMIN, AR_OPCODE_DMAX,
            AR_OPCODE_DDIV, AR_OPCODE_DSQRT, AR_OPCODE_DSIN, AR_OPCODE_UNKNOWN,
            AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN, AR_OPCODE_UNKNOWN
        }
};

struct ArInstruction_T instruction_decode(uint32_t raw, uint8_t instruction_id) {
    struct ArInstruction_T instruction;
    instruction.unit = AR_PROCESSOR_UNIT_UNKNOWN;
    instruction.swt = 0;
    instruction.parameters.size = BITS(raw, 8, 2);
    instruction.parameters.id_1 = BITS(raw, 8, 2);
    instruction.parameters.id_2 = BITS(raw, 10, 2);
    instruction.parameters.small_immediate = BITS(raw, 10, 9);
    instruction.parameters.medium_immediate = BITS(raw, 10, 16);
    instruction.parameters.long_immediate = (BITS(raw, 4, 4) << 16) | BITS(raw, 10, 16);
    instruction.parameters.reg_c = BITS(raw, 14, 5);
    instruction.parameters.reg_b = BITS(raw, 20, 5);
    instruction.parameters.reg_a = BITS(raw, 26, 5);

    instruction.unit = instruction_decode_unit[BITS(raw, 0, 2)][instruction_id];
    instruction.opcode = instruction_decode_opcodes[instruction.unit][BITS(raw, 2, 6)];

    if(instruction.opcode == AR_OPCODE_SWT) {
        instruction.swt = 1;
        instruction.unit = instruction_decode_unit_swt[BITS(raw, 4, 4)];
        instruction.opcode = instruction_decode_opcodes_swt[BITS(raw, 4, 4)][BITS(raw, 10, 4)];
    }

    return instruction;
}

void register_print(uint8_t reg) {
    printf("r%hhu", reg);
}

void vregister_print(uint8_t reg) {
    printf("v%hhu", reg);
}

void viregister_print(uint8_t reg, uint8_t id) {
    printf("v%hhu.", reg);
    switch (id) {
        case 0:
            printf("x");
            break;
        case 1:
            printf("y");
            break;
        case 2:
            printf("z");
            break;
        case 3:
            printf("t");
            break;
    }
}

void unit_print(enum ArUnit unit) {
    switch (unit) {
        case AR_PROCESSOR_UNIT_ALU1:
            printf("ALU1");
            break;
        case AR_PROCESSOR_UNIT_ALU2:
            printf("ALU2");
            break;
        case AR_PROCESSOR_UNIT_ALU3:
            printf("ALU3");
            break;
        case AR_PROCESSOR_UNIT_ALU4:
            printf("ALU4");
            break;
        case AR_PROCESSOR_UNIT_CMP:
            printf("CMP");
            break;
        case AR_PROCESSOR_UNIT_VFPU:
            printf("VFPU");
            break;
        case AR_PROCESSOR_UNIT_DMA:
            printf("DMA");
            break;
        case AR_PROCESSOR_UNIT_LSU1:
            printf("LSU1");
            break;
        case AR_PROCESSOR_UNIT_LSU2:
            printf("LSU2");
            break;
        case AR_PROCESSOR_UNIT_UNKNOWN:
            printf("UNKNOWN");
            break;
    }
}

void instruction_print(struct ArInstruction_T *instruction) {
    switch (instruction->opcode) {
        case AR_OPCODE_UNKNOWN:
            printf("UNKNOWN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMA:
            printf("LDDMA(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STDMA:
            printf("STDMA(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMAR:
            printf("LDDMAR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STDMAR:
            printf("STDMAR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMAIR:
            printf("DMAIR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMAL:
            printf("LDDMAL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STDMAL:
            printf("STDMAL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CLEARC:
            printf("CLEARC(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_WAIT:
            printf("WAIT(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDM:
            printf("LDM(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDMI:
            printf("LDMI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STM:
            printf("STM(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STMI:
            printf("STMI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDC:
            printf("LDC(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDCI:
            printf("LDCI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STC:
            printf("STC(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STCI:
            printf("STCI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_IN:
            printf("IN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_OUT:
            printf("OUT(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_OUTI:
            printf("OUTI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDMV:
            printf("LDMV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDMVI:
            printf("LDMVI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDCV:
            printf("LDCV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDCVI:
            printf("LDCVI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STMV:
            printf("STMV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STMVI:
            printf("STMVI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STCV:
            printf("STCV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STCVI:
            printf("STCVI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDMIL:
            printf("LDMIL(");
            unit_print(instruction->unit);
            printf(", ");
            register_print(instruction->parameters.reg_a);
            printf(", %hu", instruction->parameters.medium_immediate);
            printf(")");
            break;
        case AR_OPCODE_STMIL:
            printf("STMIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDCIL:
            printf("LDCIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STCIL:
            printf("STCIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_PREFETCHI:
            printf("PREFETCHI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FLUSHI:
            printf("FLUSHI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_PREFETCH:
            printf("PREFETCH(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FLUSH:
            printf("FLUSH(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDMVIL:
            printf("LDMVIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STMVIL:
            printf("STMVIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDCVIL:
            printf("LDCVIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STCVIL:
            printf("STCVIL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_NOP:
            printf("NOP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVEI:
            printf("MOVEI(");
            unit_print(instruction->unit);
            printf(", ");
            register_print(instruction->parameters.reg_a);
            printf(", %u", instruction->parameters.long_immediate);
            printf(")");
            break;
        case AR_OPCODE_MOVEINS:
            printf("MOVEINS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVEFR:
            printf("MOVEFR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVEIR:
            printf("MOVEIR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVECYC:
            printf("MOVECYC(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVELRL:
            printf("MOVELRL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVELRS:
            printf("MOVELRS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVEBR:
            printf("MOVEBR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ADD:
            printf("ADD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ADDI:
            printf("ADDI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ADDQ:
            printf("ADDQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_SUB:
            printf("SUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_SUBI:
            printf("SUBI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_SUBQ:
            printf("SUBQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULS:
            printf("MULS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULSI:
            printf("MULSI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULSQ:
            printf("MULSQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULU:
            printf("MULU(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULUI:
            printf("MULUI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MULUQ:
            printf("MULUQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVS:
            printf("DIVS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVSI:
            printf("DIVSI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVSQ:
            printf("DIVSQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVU:
            printf("DIVU(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVUI:
            printf("DIVUI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DIVUQ:
            printf("DIVUQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_AND:
            printf("AND(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ANDI:
            printf("ANDI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ANDQ:
            printf("ANDQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_OR:
            printf("OR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ORI:
            printf("ORI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ORQ:
            printf("ORQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_XOR:
            printf("XOR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_XORI:
            printf("XORI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_XORQ:
            printf("XORQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASL:
            printf("ASL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASLI:
            printf("ASLI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASLQ:
            printf("ASLQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSL:
            printf("LSL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSLI:
            printf("LSLI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSLQ:
            printf("LSLQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASR:
            printf("ASR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASRI:
            printf("ASRI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ASRQ:
            printf("ASRQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSR:
            printf("LSR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSRI:
            printf("LSRI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LSRQ:
            printf("LSRQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_REMS:
            printf("REMS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_REMU:
            printf("REMU(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_REMSI:
            printf("REMSI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_REMUI:
            printf("REMUI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CMP:
            printf("CMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CMPI:
            printf("CMPI(");
            unit_print(instruction->unit);
            printf(", ");
            register_print(instruction->parameters.reg_a);
            printf(", %u", instruction->parameters.long_immediate);
            printf(")");
            break;
        case AR_OPCODE_PCMP:
            printf("PCMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_PCMPI:
            printf("PCMPI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FCMP:
            printf("FCMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DCMP:
            printf("DCMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FCMPI:
            printf("FCMPI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DCMPI:
            printf("DCMPI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BNE:
            printf("BNE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BEQ:
            printf("BEQ(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BL:
            printf("BL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BLE:
            printf("BLE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BG:
            printf("BG(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BGE:
            printf("BGE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BLS:
            printf("BLS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BLES:
            printf("BLES(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BGS:
            printf("BGS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BGES:
            printf("BGES(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_BRA:
            printf("BRA(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_JMP:
            printf("JMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_JUMP:
            printf("JUMP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_JUMPBR:
            printf("JUMPBR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CALL:
            printf("CALL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CALLBR:
            printf("CALLBR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_JMPR:
            printf("JMPR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_CALLR:
            printf("CALLR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_SWT:
            printf("SWT(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_ENDP:
            printf("ENDP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_RET:
            printf("RET(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_INT:
            printf("INT(");
            unit_print(instruction->unit);
            printf(", ");
            printf("%hu", instruction->parameters.medium_immediate);
            printf(")");
            break;
        case AR_OPCODE_RETI:
            printf("RETI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_MOVE:
            printf("MOVE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FADD:
            printf("FADD(");
            unit_print(instruction->unit);
            printf(", ");
            vregister_print(instruction->parameters.reg_a);
            printf(", ");
            viregister_print(instruction->parameters.reg_b, instruction->parameters.id_1);
            printf(", ");
            viregister_print(instruction->parameters.reg_c, instruction->parameters.id_2);
            printf(")");
            break;
        case AR_OPCODE_FSUB:
            printf("FSUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMUL:
            printf("FMUL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMULADD:
            printf("FMULADD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFADD:
            printf("VFADD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFSUB:
            printf("VFSUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMUL:
            printf("VFMUL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMULADD:
            printf("VFMULADD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFADDS:
            printf("VFADDS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFSUBS:
            printf("VFSUBS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMULS:
            printf("VFMULS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMULADDS:
            printf("VFMULADDS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMULSUB:
            printf("FMULSUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMULSUB:
            printf("VFMULSUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMULSUBS:
            printf("VFMULSUBS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFSHUFFLE:
            printf("VFSHUFFLE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMOVE:
            printf("FMOVE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFMOVE:
            printf("VFMOVE(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMOVEI:
            printf("VFMOVE(");
            unit_print(instruction->unit);
            printf(", ");
            register_print(instruction->parameters.reg_a);
            printf(", %hu", instruction->parameters.small_immediate);
            printf(")");
            break;
        case AR_OPCODE_VFMOVEI:
            printf("VFMOVEI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FNEG:
            printf("FNEG(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FABS:
            printf("FABS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFNEG:
            printf("VFNEG(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFABS:
            printf("VFABS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFTOH:
            printf("VFTOH(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VHTOF:
            printf("VHTOF(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFTOI:
            printf("VFTOI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VITOF:
            printf("VITOF(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VFTOD:
            printf("VFTOD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_VDTOF:
            printf("VDTOF(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMIN:
            printf("FMIN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FMAX:
            printf("FMAX(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FDIV:
            printf("FDIV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FSQRT:
            printf("FSQRT(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FATAN:
            printf("FATAN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FATAN2:
            break;
        case AR_OPCODE_FEXP:
            printf("FEXP(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FSUM:
            printf("FSUM(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FIPR:
            printf("FIPR(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_FSIN:
            printf("FSIN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMOVEI:
            printf("DMOVEI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DADD:
            printf("DADD(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DSUB:
            printf("DSUB(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMUL:
            printf("DMUL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DABS:
            printf("DABS(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DNEG:
            printf("DNEG(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMIN:
            printf("DMIN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMAX:
            printf("DMAX(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DDIV:
            printf("DDIV(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DSQRT:
            printf("DSQRT(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DSIN:
            printf("DSIN(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMACL:
            printf("LDDMACL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STDMACL:
            printf("STDMACL(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMAI:
            printf("DMAI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMAI:
            printf("LDDMAI(");
            unit_print(instruction->unit);
            printf(", ");
            register_print(instruction->parameters.reg_a);
            printf(", ");
            register_print(instruction->parameters.reg_b);
            printf(", %hu", instruction->parameters.small_immediate);
            printf(")");
            break;
        case AR_OPCODE_STDMAI:
            printf("STDMAI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_LDDMACLI:
            printf("LDDMACLI(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_DMAII:
            printf("DMAII(");
            unit_print(instruction->unit);
            printf(")");
            break;
        case AR_OPCODE_STDMACLI:
            printf("STDMACLI(");
            unit_print(instruction->unit);
            printf(")");
            break;
    }
}