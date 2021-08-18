#include <stdio.h>
#include "instruction.h"


void (*instruction_decode_functions[])(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id) = {
        instruction_decode_00_00,
        instruction_decode_10_00,
        instruction_decode_01_00,
        instruction_decode_11_00,

        instruction_decode_00_10,
        instruction_decode_10_10,
        instruction_decode_01_10,
        instruction_decode_11_10,

        instruction_decode_00_01,
        instruction_decode_10_01,
        instruction_decode_01_01,
        instruction_decode_11_01,


        instruction_decode_00_11,
        instruction_decode_10_11,
        instruction_decode_01_11,
        instruction_decode_11_11,
};

void instruction_decode_00_00(uint32_t raw, struct ArInstruction_T * instruction, uint8_t instruction_id) {
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_CMP;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_FCMP;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_DCMP;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_FCMPI;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_DCMPI;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_ENDP;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_RET;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_INT;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_RETI;
            break;
    }
}

void instruction_decode_00_01(uint32_t raw, struct ArInstruction_T * instruction) {}

void instruction_decode_00_10(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 16);
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_BNE;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_BEQ;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_BL;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_BLE;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_BG;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_BGE;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_BLS;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_BLES;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_BGS;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_BGES;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_BRA;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_JUMP;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_JUMPBR;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_CALL;
            break;
        case 0b1110:
            instruction->opcode = AR_OPCODE_CALLBR;
            break;
    }
}

void instruction_decode_00_11(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->opcode = AR_OPCODE_CMPI;
    instruction->parameters.immediate = (BITS(raw, 4, 4) << 10) | BITS(raw, 10, 16);
}

void instruction_decode_01_00(uint32_t raw, struct ArInstruction_T * instruction) {
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_ADD;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_SUB;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_XOR;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_OR;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_AND;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_LSL;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_ASR;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_LSR;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_MULS;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_MULU;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_DIVS;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_DIVU;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_REMS;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_REMU;
            break;
    }
}

void instruction_decode_01_01(uint32_t raw, struct ArInstruction_T * instruction) {
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_NOP;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_MOVEINS;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_MOVECYC;
            break;
        case 0b1110:
            instruction->opcode = AR_OPCODE_MOVEFR;
            break;
        case 0b1111:
            instruction->opcode = AR_OPCODE_MOVEIR;
            break;

    }
}

void instruction_decode_01_10(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 9);

    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_ADDI;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_SUBI;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_XORI;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_ORI;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_ANDI;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_LSLI;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_ASRI;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_LSRI;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_MULSI;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_MULUI;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_DIVSI;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_DIVUI;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_REMSI;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_REMUI;
            break;
    }
}

void instruction_decode_01_11(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->opcode = AR_OPCODE_MOVEI;
    instruction->parameters.immediate = (BITS(raw, 6, 4)) << 10 | BITS(raw, 10, 16) ;
}

void instruction_decode_10_00(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 9);
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_LDM;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_STM;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_LDC;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_STC;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_LDMI;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_STMI;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_LDCI;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_STCI;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_LDMV;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_STMV;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_LDCV;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_STCV;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_LDMVI;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_STMVI;
            break;
        case 0b1110:
            instruction->opcode = AR_OPCODE_LDCVI;
            break;
        case 0b1111:
            instruction->opcode = AR_OPCODE_STCVI;
            break;
    }
}

void instruction_decode_10_01(uint32_t raw, struct ArInstruction_T * instruction) {}

void instruction_decode_10_10(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 13) ;
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_LDMIL;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_STMIL;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_LDCIL;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_STCIL;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_PREFETCHI;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_FLUSHI;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_PREFETCH;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_FLUSH;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_LDMVIL;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_STMVIL;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_LDCVIL;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_STCVIL;
            break;
    }
}

void instruction_decode_10_11(uint32_t raw, struct ArInstruction_T * instruction) {}

void instruction_decode_11_00(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 9);
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_FADD;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_FSUB;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_FMUL;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_FMULADD;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_VFADD;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_VFSUB;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_VFMUL;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_VFMULADD;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_VFADDS;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_VFSUBS;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_VFMULS;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_VFMULADDS;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_FMULSUB;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_VFMULSUB;
            break;
        case 0b1110:
            instruction->opcode = AR_OPCODE_VFMULSUBS;
            break;
        case 0b1111:
            instruction->opcode = AR_OPCODE_VFSHUFFLE;
            break;
    }
}

void instruction_decode_11_01(uint32_t raw, struct ArInstruction_T * instruction) {
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_FDIV;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_FSQRT;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_FATAN;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_FATAN2;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_FEXP;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_FSUM;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_FIPR;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_FSIN;
            break;
    }
}

void instruction_decode_11_10(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 13);
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_FMOVE;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_VFMOVE;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_FMOVEI;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_VFMOVEI;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_FNEG;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_FABS;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_VFNEG;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_VFABS;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_VFTOH;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_VHTOF;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_VFTOI;
            break;
        case 0b1011:
            instruction->opcode = AR_OPCODE_VITOF;
            break;
        case 0b1100:
            instruction->opcode = AR_OPCODE_VFTOD;
            break;
        case 0b1101:
            instruction->opcode = AR_OPCODE_VDTOF;
            break;
        case 0b1110:
            instruction->opcode = AR_OPCODE_FMIN;
            break;
        case 0b1111:
            instruction->opcode = AR_OPCODE_FMAX;
            break;
    }
}

void instruction_decode_11_11(uint32_t raw, struct ArInstruction_T * instruction) {
    instruction->parameters.immediate = BITS(raw, 10, 13);
    switch (BITS(raw, 4, 4)) {
        case 0b0000:
            instruction->opcode = AR_OPCODE_DMOVEI;
            break;
        case 0b0001:
            instruction->opcode = AR_OPCODE_DADD;
            break;
        case 0b0010:
            instruction->opcode = AR_OPCODE_DSUB;
            break;
        case 0b0011:
            instruction->opcode = AR_OPCODE_DMUL;
            break;
        case 0b0100:
            instruction->opcode = AR_OPCODE_DABS;
            break;
        case 0b0101:
            instruction->opcode = AR_OPCODE_DNEG;
            break;
        case 0b0110:
            instruction->opcode = AR_OPCODE_DMIN;
            break;
        case 0b0111:
            instruction->opcode = AR_OPCODE_DMAX;
            break;
        case 0b1000:
            instruction->opcode = AR_OPCODE_DDIV;
            break;
        case 0b1001:
            instruction->opcode = AR_OPCODE_DSQRT;
            break;
        case 0b1010:
            instruction->opcode = AR_OPCODE_DSIN;
            break;
    }
}


enum ArUnit instruction_get_unit(enum ArOpcode opcode, uint8_t instruction_id) {
    switch (opcode) {
        case AR_OPCODE_ADD:
        case AR_OPCODE_SUB:
        case AR_OPCODE_XOR:
        case AR_OPCODE_OR:
        case AR_OPCODE_AND:
        case AR_OPCODE_LSL:
        case AR_OPCODE_ASR:
        case AR_OPCODE_LSR:
        case AR_OPCODE_MULS:
        case AR_OPCODE_MULU:
        case AR_OPCODE_DIVS:
        case AR_OPCODE_DIVU:
        case AR_OPCODE_REMS:
        case AR_OPCODE_REMU:
        case AR_OPCODE_ADDI:
        case AR_OPCODE_SUBI:
        case AR_OPCODE_XORI:
        case AR_OPCODE_ORI:
        case AR_OPCODE_ANDI:
        case AR_OPCODE_LSLI:
        case AR_OPCODE_ASRI:
        case AR_OPCODE_LSRI:
        case AR_OPCODE_MULSI:
        case AR_OPCODE_MULUI:
        case AR_OPCODE_DIVSI:
        case AR_OPCODE_DIVUI:
        case AR_OPCODE_REMSI:
        case AR_OPCODE_REMUI:
        case AR_OPCODE_NOP:
        case AR_OPCODE_MOVEINS:
        case AR_OPCODE_MOVECYC:
        case AR_OPCODE_MOVEFR:
        case AR_OPCODE_MOVEIR:
            if(instruction_id == 0) {
                return AR_PROCESSOR_UNIT_ALU1;
            } else if(instruction_id == 1) {
                return AR_PROCESSOR_UNIT_ALU2;
            } else if(instruction_id == 2) {
                return AR_PROCESSOR_UNIT_ALU3;
            } else if(instruction_id == 3) {
                return AR_PROCESSOR_UNIT_ALU4;
            }
            break;
        case AR_OPCODE_LDM:
        case AR_OPCODE_STM:
        case AR_OPCODE_LDC:
        case AR_OPCODE_STC:
        case AR_OPCODE_LDMI:
        case AR_OPCODE_STMI:
        case AR_OPCODE_LDCI:
        case AR_OPCODE_STCI:
        case AR_OPCODE_LDMV:
        case AR_OPCODE_STMV:
        case AR_OPCODE_LDCV:
        case AR_OPCODE_STCV:
        case AR_OPCODE_LDMVI:
        case AR_OPCODE_STMVI:
        case AR_OPCODE_LDCVI:
        case AR_OPCODE_STCVI:
        case AR_OPCODE_LDMIL:
        case AR_OPCODE_STMIL:
        case AR_OPCODE_LDCIL:
        case AR_OPCODE_STCIL:
        case AR_OPCODE_LDMVIL:
        case AR_OPCODE_STMVIL:
        case AR_OPCODE_LDCVIL:
        case AR_OPCODE_STCVIL:
        case AR_OPCODE_PREFETCH:
        case AR_OPCODE_FLUSH:
        case AR_OPCODE_PREFETCHI:
        case AR_OPCODE_FLUSHI:
            if (instruction_id == 0 || instruction_id == 2) {
                return AR_PROCESSOR_UNIT_LSU1;
            } else if (instruction_id == 1 || instruction_id == 3) {
                return AR_PROCESSOR_UNIT_LSU2;
            }
            break;
        case AR_OPCODE_CMP:
        case AR_OPCODE_FCMP:
        case AR_OPCODE_DCMP:
        case AR_OPCODE_FCMPI:
        case AR_OPCODE_DCMPI:
        case AR_OPCODE_ENDP:
        case AR_OPCODE_RET:
        case AR_OPCODE_RETI:
        case AR_OPCODE_INT:
        case AR_OPCODE_CMPI:
        case AR_OPCODE_BNE:
        case AR_OPCODE_BEQ:
        case AR_OPCODE_BL:
        case AR_OPCODE_BLE:
        case AR_OPCODE_BG:
        case AR_OPCODE_BGE:
        case AR_OPCODE_BLS:
        case AR_OPCODE_BLES:
        case AR_OPCODE_BGS:
        case AR_OPCODE_BGES:
        case AR_OPCODE_BRA:
        case AR_OPCODE_JUMP:
        case AR_OPCODE_JUMPBR:
        case AR_OPCODE_CALL:
        case AR_OPCODE_CALLBR:
            if(instruction_id == 0) {
                return AR_PROCESSOR_UNIT_CMP;
            }
            break;
        case AR_OPCODE_FADD:
        case AR_OPCODE_FSUB:
        case AR_OPCODE_FMUL:
        case AR_OPCODE_FMULADD:
        case AR_OPCODE_VFADD:
        case AR_OPCODE_VFSUB:
        case AR_OPCODE_VFMUL:
        case AR_OPCODE_VFMULADD:
        case AR_OPCODE_VFADDS:
        case AR_OPCODE_VFSUBS:
        case AR_OPCODE_VFMULS:
        case AR_OPCODE_VFMULADDS:
        case AR_OPCODE_FMULSUB:
        case AR_OPCODE_VFMULSUB:
        case AR_OPCODE_VFMULSUBS:
        case AR_OPCODE_VFSHUFFLE:
        case AR_OPCODE_FMOVE:
        case AR_OPCODE_VFMOVE:
        case AR_OPCODE_FMOVEI:
        case AR_OPCODE_VFMOVEI:
        case AR_OPCODE_FNEG:
        case AR_OPCODE_FABS:
        case AR_OPCODE_VFNEG:
        case AR_OPCODE_VFABS:
        case AR_OPCODE_VFTOH:
        case AR_OPCODE_VHTOF:
        case AR_OPCODE_VFTOI:
        case AR_OPCODE_VITOF:
        case AR_OPCODE_VFTOD:
        case AR_OPCODE_VDTOF:
        case AR_OPCODE_FMIN:
        case AR_OPCODE_FMAX:
        case AR_OPCODE_FDIV:
        case AR_OPCODE_FSQRT:
        case AR_OPCODE_FATAN:
        case AR_OPCODE_FATAN2:
        case AR_OPCODE_FEXP:
        case AR_OPCODE_FSUM:
        case AR_OPCODE_FIPR:
        case AR_OPCODE_FSIN:
        case AR_OPCODE_DMOVEI:
        case AR_OPCODE_DADD:
        case AR_OPCODE_DSUB:
        case AR_OPCODE_DMUL:
        case AR_OPCODE_DABS:
        case AR_OPCODE_DNEG:
        case AR_OPCODE_DMIN:
        case AR_OPCODE_DMAX:
        case AR_OPCODE_DDIV:
        case AR_OPCODE_DSQRT:
        case AR_OPCODE_DSIN:
            return AR_PROCESSOR_UNIT_VFPU;
    }
    return AR_PROCESSOR_UNIT_UNKNOWN;
}

struct ArInstruction_T instruction_decode(uint32_t raw, uint8_t instruction_id) {
    struct ArInstruction_T instruction;
    instruction.unit = AR_PROCESSOR_UNIT_UNKNOWN;
    instruction.parameters.size  = BITS(raw, 8, 2);
    instruction.parameters.reg_a = BITS(raw, 26, 5);
    instruction.parameters.reg_b = BITS(raw, 20, 5);
    instruction.parameters.reg_c = BITS(raw, 14, 5);
    instruction.parameters.id_1  = BITS(raw, 8, 2);
    instruction.parameters.id_2  = BITS(raw, 10, 2);
    instruction_decode_functions[BITS(raw, 0, 4)](raw, &instruction, instruction_id);
    return instruction;
}

void print_instruction(struct ArInstruction_T * instruction) {
    switch (instruction->opcode) {
        case AR_OPCODE_UNKNOWN:
            printf("AR_OPCODE_UNKNOWN");
            break;
        case AR_OPCODE_LDDMA:
            printf("AR_OPCODE_LDDMA");
            break;
        case AR_OPCODE_STDMA:
            printf("AR_OPCODE_STDMA");
            break;
        case AR_OPCODE_LDDMAR:
            printf("AR_OPCODE_LDDMAR");
            break;
        case AR_OPCODE_STDMAR:
            printf("AR_OPCODE_STDMAR");
            break;
        case AR_OPCODE_DMAIR:
            printf("AR_OPCODE_DMAIR");
            break;
        case AR_OPCODE_LDDMAL:
            printf("AR_OPCODE_LDDMAL");
            break;
        case AR_OPCODE_STDMAL:
            printf("AR_OPCODE_STDMAL");
            break;
        case AR_OPCODE_CLEARC:
            printf("AR_OPCODE_CLEARC");
            break;
        case AR_OPCODE_WAIT:
            printf("AR_OPCODE_WAIT");
            break;
        case AR_OPCODE_LDM:
            printf("AR_OPCODE_LDM");
            break;
        case AR_OPCODE_LDMI:
            printf("AR_OPCODE_LDMI");
            break;
        case AR_OPCODE_STM:
            printf("AR_OPCODE_STM");
            break;
        case AR_OPCODE_STMI:
            printf("AR_OPCODE_STMI");
            break;
        case AR_OPCODE_LDC:
            printf("AR_OPCODE_LDC");
            break;
        case AR_OPCODE_LDCI:
            printf("AR_OPCODE_LDCI");
            break;
        case AR_OPCODE_STC:
            printf("AR_OPCODE_STC");
            break;
        case AR_OPCODE_STCI:
            printf("AR_OPCODE_STCI");
            break;
        case AR_OPCODE_IN:
            printf("AR_OPCODE_IN");
            break;
        case AR_OPCODE_OUT:
            printf("AR_OPCODE_OUT");
            break;
        case AR_OPCODE_OUTI:
            printf("AR_OPCODE_OUTI");
            break;
        case AR_OPCODE_LDMV:
            printf("AR_OPCODE_LDMV");
            break;
        case AR_OPCODE_LDMVI:
            printf("AR_OPCODE_LDMVI");
            break;
        case AR_OPCODE_LDCV:
            printf("AR_OPCODE_LDCV");
            break;
        case AR_OPCODE_LDCVI:
            printf("AR_OPCODE_LDCVI");
            break;
        case AR_OPCODE_STMV:
            printf("AR_OPCODE_STMV");
            break;
        case AR_OPCODE_STMVI:
            printf("AR_OPCODE_STMVI");
            break;
        case AR_OPCODE_STCV:
            printf("AR_OPCODE_STCV");
            break;
        case AR_OPCODE_STCVI:
            printf("AR_OPCODE_STCVI");
            break;
        case AR_OPCODE_LDMIL:
            printf("AR_OPCODE_LDMIL");
            break;
        case AR_OPCODE_STMIL:
            printf("AR_OPCODE_STMIL");
            break;
        case AR_OPCODE_LDCIL:
            printf("AR_OPCODE_LDCIL");
            break;
        case AR_OPCODE_STCIL:
            printf("AR_OPCODE_STCIL");
            break;
        case AR_OPCODE_PREFETCHI:
            printf("AR_OPCODE_PREFETCHI");
            break;
        case AR_OPCODE_FLUSHI:
            printf("AR_OPCODE_FLUSHI");
            break;
        case AR_OPCODE_PREFETCH:
            printf("AR_OPCODE_PREFETCH");
            break;
        case AR_OPCODE_FLUSH:
            printf("AR_OPCODE_FLUSH");
            break;
        case AR_OPCODE_LDMVIL:
            printf("AR_OPCODE_LDMVIL");
            break;
        case AR_OPCODE_STMVIL:
            printf("AR_OPCODE_STMVIL");
            break;
        case AR_OPCODE_LDCVIL:
            printf("AR_OPCODE_LDCVIL");
            break;
        case AR_OPCODE_STCVIL:
            printf("AR_OPCODE_STCVIL");
            break;
        case AR_OPCODE_NOP:
            printf("AR_OPCODE_NOP");
            break;
        case AR_OPCODE_MOVEI:
            printf("AR_OPCODE_MOVEI");
            break;
        case AR_OPCODE_MOVEINS:
            printf("AR_OPCODE_MOVEINS");
            break;
        case AR_OPCODE_MOVEFR:
            printf("AR_OPCODE_MOVEFR");
            break;
        case AR_OPCODE_MOVEIR:
            printf("AR_OPCODE_MOVEIR");
            break;
        case AR_OPCODE_MOVECYC:
            printf("AR_OPCODE_MOVECYC");
            break;
        case AR_OPCODE_MOVELRL:
            printf("AR_OPCODE_MOVELRL");
            break;
        case AR_OPCODE_MOVELRS:
            printf("AR_OPCODE_MOVELRS");
            break;
        case AR_OPCODE_MOVEBR:
            printf("AR_OPCODE_MOVEBR");
            break;
        case AR_OPCODE_ADD:
            printf("AR_OPCODE_ADD");
            break;
        case AR_OPCODE_ADDI:
            printf("AR_OPCODE_ADDI");
            break;
        case AR_OPCODE_ADDQ:
            printf("AR_OPCODE_ADDQ");
            break;
        case AR_OPCODE_SUB:
            printf("AR_OPCODE_SUB");
            break;
        case AR_OPCODE_SUBI:
            printf("AR_OPCODE_SUBI");
            break;
        case AR_OPCODE_SUBQ:
            printf("AR_OPCODE_SUBQ");
            break;
        case AR_OPCODE_MULS:
            printf("AR_OPCODE_MULS");
            break;
        case AR_OPCODE_MULSI:
            printf("AR_OPCODE_MULSI");
            break;
        case AR_OPCODE_MULSQ:
            printf("AR_OPCODE_MULSQ");
            break;
        case AR_OPCODE_MULU:
            printf("AR_OPCODE_MULU");
            break;
        case AR_OPCODE_MULUI:
            printf("AR_OPCODE_MULUI");
            break;
        case AR_OPCODE_MULUQ:
            printf("AR_OPCODE_MULUQ");
            break;
        case AR_OPCODE_DIVS:
            printf("AR_OPCODE_DIVS");
            break;
        case AR_OPCODE_DIVSI:
            printf("AR_OPCODE_DIVSI");
            break;
        case AR_OPCODE_DIVSQ:
            printf("AR_OPCODE_DIVSQ");
            break;
        case AR_OPCODE_DIVU:
            printf("AR_OPCODE_DIVU");
            break;
        case AR_OPCODE_DIVUI:
            printf("AR_OPCODE_DIVUI");
            break;
        case AR_OPCODE_DIVUQ:
            printf("AR_OPCODE_DIVUQ");
            break;
        case AR_OPCODE_AND:
            printf("AR_OPCODE_AND");
            break;
        case AR_OPCODE_ANDI:
            printf("AR_OPCODE_ANDI");
            break;
        case AR_OPCODE_ANDQ:
            printf("AR_OPCODE_ANDQ");
            break;
        case AR_OPCODE_OR:
            printf("AR_OPCODE_OR");
            break;
        case AR_OPCODE_ORI:
            printf("AR_OPCODE_ORI");
            break;
        case AR_OPCODE_ORQ:
            printf("AR_OPCODE_ORQ");
            break;
        case AR_OPCODE_XOR:
            printf("AR_OPCODE_XOR");
            break;
        case AR_OPCODE_XORI:
            printf("AR_OPCODE_XORI");
            break;
        case AR_OPCODE_XORQ:
            printf("AR_OPCODE_XORQ");
            break;
        case AR_OPCODE_ASL:
            printf("AR_OPCODE_ASL");
            break;
        case AR_OPCODE_ASLI:
            printf("AR_OPCODE_ASLI");
            break;
        case AR_OPCODE_ASLQ:
            printf("AR_OPCODE_ASLQ");
            break;
        case AR_OPCODE_LSL:
            printf("AR_OPCODE_LSL");
            break;
        case AR_OPCODE_LSLI:
            printf("AR_OPCODE_LSLI");
            break;
        case AR_OPCODE_LSLQ:
            printf("AR_OPCODE_LSLQ");
            break;
        case AR_OPCODE_ASR:
            printf("AR_OPCODE_ASR");
            break;
        case AR_OPCODE_ASRI:
            printf("AR_OPCODE_ASRI");
            break;
        case AR_OPCODE_ASRQ:
            printf("AR_OPCODE_ASRQ");
            break;
        case AR_OPCODE_LSR:
            printf("AR_OPCODE_LSR");
            break;
        case AR_OPCODE_LSRI:
            printf("AR_OPCODE_LSRI");
            break;
        case AR_OPCODE_LSRQ:
            printf("AR_OPCODE_LSRQ");
            break;
        case AR_OPCODE_REMS:
            printf("AR_OPCODE_REMS");
            break;
        case AR_OPCODE_REMU:
            printf("AR_OPCODE_REMU");
            break;
        case AR_OPCODE_REMSI:
            printf("AR_OPCODE_REMSI");
            break;
        case AR_OPCODE_REMUI:
            printf("AR_OPCODE_REMUI");
            break;
        case AR_OPCODE_CMP:
            printf("AR_OPCODE_CMP");
            break;
        case AR_OPCODE_CMPI:
            printf("AR_OPCODE_CMPI");
            break;
        case AR_OPCODE_PCMP:
            printf("AR_OPCODE_PCMP");
            break;
        case AR_OPCODE_PCMPI:
            printf("AR_OPCODE_PCMPI");
            break;
        case AR_OPCODE_FCMP:
            printf("AR_OPCODE_FCMP");
            break;
        case AR_OPCODE_DCMP:
            printf("AR_OPCODE_DCMP");
            break;
        case AR_OPCODE_FCMPI:
            printf("AR_OPCODE_FCMPI");
            break;
        case AR_OPCODE_DCMPI:
            printf("AR_OPCODE_DCMPI");
            break;
        case AR_OPCODE_BNE:
            printf("AR_OPCODE_BNE");
            break;
        case AR_OPCODE_BEQ:
            printf("AR_OPCODE_BEQ");
            break;
        case AR_OPCODE_BL:
            printf("AR_OPCODE_BL");
            break;
        case AR_OPCODE_BLE:
            printf("AR_OPCODE_BLE");
            break;
        case AR_OPCODE_BG:
            printf("AR_OPCODE_BG");
            break;
        case AR_OPCODE_BGE:
            printf("AR_OPCODE_BGE");
            break;
        case AR_OPCODE_BLS:
            printf("AR_OPCODE_BLS");
            break;
        case AR_OPCODE_BLES:
            printf("AR_OPCODE_BLES");
            break;
        case AR_OPCODE_BGS:
            printf("AR_OPCODE_BGS");
            break;
        case AR_OPCODE_BGES:
            printf("AR_OPCODE_BGES");
            break;
        case AR_OPCODE_BRA:
            printf("AR_OPCODE_BRA");
            break;
        case AR_OPCODE_JMP:
            printf("AR_OPCODE_JMP");
            break;
        case AR_OPCODE_JUMP:
            printf("AR_OPCODE_JUMP");
            break;
        case AR_OPCODE_JUMPBR:
            printf("AR_OPCODE_JUMPBR");
            break;
        case AR_OPCODE_CALL:
            printf("AR_OPCODE_CALL");
            break;
        case AR_OPCODE_CALLBR:
            printf("AR_OPCODE_CALLBR");
            break;
        case AR_OPCODE_JMPR:
            printf("AR_OPCODE_JMPR");
            break;
        case AR_OPCODE_CALLR:
            printf("AR_OPCODE_CALLR");
            break;
        case AR_OPCODE_SWT:
            printf("AR_OPCODE_SWT");
            break;
        case AR_OPCODE_ENDP:
            printf("AR_OPCODE_ENDP");
            break;
        case AR_OPCODE_RET:
            printf("AR_OPCODE_RET");
            break;
        case AR_OPCODE_INT:
            printf("AR_OPCODE_INT");
            break;
        case AR_OPCODE_RETI:
            printf("AR_OPCODE_RETI");
            break;
        case AR_OPCODE_MOVE:
            printf("AR_OPCODE_MOVE");
            break;
        case AR_OPCODE_FADD:
            printf("AR_OPCODE_FADD(%hhu, %hhu_%hhu, %hhu_%hhu)", instruction->parameters.reg_a, instruction->parameters.reg_b, instruction->parameters.id_1, instruction->parameters.reg_c, instruction->parameters.id_2);
            break;
        case AR_OPCODE_FSUB:
            printf("AR_OPCODE_FSUB");
            break;
        case AR_OPCODE_FMUL:
            printf("AR_OPCODE_FMUL");
            break;
        case AR_OPCODE_FMULADD:
            printf("AR_OPCODE_FMULADD");
            break;
        case AR_OPCODE_VFADD:
            printf("AR_OPCODE_VFADD");
            break;
        case AR_OPCODE_VFSUB:
            printf("AR_OPCODE_VFSUB");
            break;
        case AR_OPCODE_VFMUL:
            printf("AR_OPCODE_VFMUL");
            break;
        case AR_OPCODE_VFMULADD:
            printf("AR_OPCODE_VFMULADD");
            break;
        case AR_OPCODE_VFADDS:
            printf("AR_OPCODE_VFADDS");
            break;
        case AR_OPCODE_VFSUBS:
            printf("AR_OPCODE_VFSUBS");
            break;
        case AR_OPCODE_VFMULS:
            printf("AR_OPCODE_VFMULS");
            break;
        case AR_OPCODE_VFMULADDS:
            printf("AR_OPCODE_VFMULADDS");
            break;
        case AR_OPCODE_FMULSUB:
            printf("AR_OPCODE_FMULSUB");
            break;
        case AR_OPCODE_VFMULSUB:
            printf("AR_OPCODE_VFMULSUB");
            break;
        case AR_OPCODE_VFMULSUBS:
            printf("AR_OPCODE_VFMULSUBS");
            break;
        case AR_OPCODE_VFSHUFFLE:
            printf("AR_OPCODE_VFSHUFFLE");
            break;
        case AR_OPCODE_FMOVE:
            printf("AR_OPCODE_FMOVE");
            break;
        case AR_OPCODE_VFMOVE:
            printf("AR_OPCODE_VFMOVE");
            break;
        case AR_OPCODE_FMOVEI:
            printf("AR_OPCODE_FMOVEI(%hhu, %u)", instruction->parameters.reg_a, instruction->parameters.immediate);
            break;
        case AR_OPCODE_VFMOVEI:
            printf("AR_OPCODE_VFMOVEI");
            break;
        case AR_OPCODE_FNEG:
            printf("AR_OPCODE_FNEG");
            break;
        case AR_OPCODE_FABS:
            printf("AR_OPCODE_FABS");
            break;
        case AR_OPCODE_VFNEG:
            printf("AR_OPCODE_VFNEG");
            break;
        case AR_OPCODE_VFABS:
            printf("AR_OPCODE_VFABS");
            break;
        case AR_OPCODE_VFTOH:
            printf("AR_OPCODE_VFTOH");
            break;
        case AR_OPCODE_VHTOF:
            printf("AR_OPCODE_VHTOF");
            break;
        case AR_OPCODE_VFTOI:
            printf("AR_OPCODE_VFTOI");
            break;
        case AR_OPCODE_VITOF:
            printf("AR_OPCODE_VITOF");
            break;
        case AR_OPCODE_VFTOD:
            printf("AR_OPCODE_VFTOD");
            break;
        case AR_OPCODE_VDTOF:
            printf("AR_OPCODE_VDTOF");
            break;
        case AR_OPCODE_FMIN:
            printf("AR_OPCODE_FMIN");
            break;
        case AR_OPCODE_FMAX:
            printf("AR_OPCODE_FMAX");
            break;
        case AR_OPCODE_FDIV:
            printf("AR_OPCODE_FDIV");
            break;
        case AR_OPCODE_FSQRT:
            printf("AR_OPCODE_FSQRT");
            break;
        case AR_OPCODE_FATAN:
            printf("AR_OPCODE_FATAN");
            break;
        case AR_OPCODE_FATAN2:
            break;
        case AR_OPCODE_FEXP:
            printf("AR_OPCODE_FEXP");
            break;
        case AR_OPCODE_FSUM:
            printf("AR_OPCODE_FSUM");
            break;
        case AR_OPCODE_FIPR:
            printf("AR_OPCODE_FIPR");
            break;
        case AR_OPCODE_FSIN:
            printf("AR_OPCODE_FSIN");
            break;
        case AR_OPCODE_DMOVEI:
            printf("AR_OPCODE_DMOVEI");
            break;
        case AR_OPCODE_DADD:
            printf("AR_OPCODE_DADD");
            break;
        case AR_OPCODE_DSUB:
            printf("AR_OPCODE_DSUB");
            break;
        case AR_OPCODE_DMUL:
            printf("AR_OPCODE_DMUL");
            break;
        case AR_OPCODE_DABS:
            printf("AR_OPCODE_DABS");
            break;
        case AR_OPCODE_DNEG:
            printf("AR_OPCODE_DNEG");
            break;
        case AR_OPCODE_DMIN:
            printf("AR_OPCODE_DMIN");
            break;
        case AR_OPCODE_DMAX:
            printf("AR_OPCODE_DMAX");
            break;
        case AR_OPCODE_DDIV:
            printf("AR_OPCODE_DDIV");
            break;
        case AR_OPCODE_DSQRT:
            printf("AR_OPCODE_DSQRT");
            break;
        case AR_OPCODE_DSIN:
            printf("AR_OPCODE_DSIN");
            break;
    }
}