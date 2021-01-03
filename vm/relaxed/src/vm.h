#ifndef ALTAIR_VM_INTERNAL_H_DEFINED
#define ALTAIR_VM_INTERNAL_H_DEFINED

#include <base/vm.h>

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

typedef struct ArVirtualMachine_T
{
    ArProcessor processor;
    ArPhysicalMemory memory;
} ArVirtualMachine_T;

typedef enum Opcode
{
    OPCODE_UNKNOWN,

    //AGU
    OPCODE_LDDMA,
    OPCODE_STDMA,
    OPCODE_LDDMAR,
    OPCODE_STDMAR,
    OPCODE_DMAIR,
    OPCODE_WAIT,

    //LSU
    OPCODE_LDM,
    OPCODE_STM,
    OPCODE_LDC,
    OPCODE_STC,
    OPCODE_LDMX,
    OPCODE_STMX,
    OPCODE_IN,
    OPCODE_OUT,
    OPCODE_OUTI,
    OPCODE_LDMV,
    OPCODE_STMV,
    OPCODE_LDCV,
    OPCODE_STCV,
    OPCODE_LDMF,
    OPCODE_STMF,
    OPCODE_LDCF,
    OPCODE_STCF,
    OPCODE_LDMD,
    OPCODE_STMD,
    OPCODE_LDCD,
    OPCODE_STCD,

    //ALU
    OPCODE_NOP,
    OPCODE_XCHG,
    //OPCODE_MOVE,
    OPCODE_MOVEI,
    OPCODE_ADD,
    OPCODE_ADDI,
    OPCODE_ADDQ,
    OPCODE_SUB,
    OPCODE_SUBI,
    OPCODE_SUBQ,
    OPCODE_MULS,
    OPCODE_MULSI,
    OPCODE_MULSQ,
    OPCODE_MULU,
    OPCODE_MULUI,
    OPCODE_MULUQ,
    OPCODE_DIVS,
    OPCODE_DIVSI,
    OPCODE_DIVSQ,
    OPCODE_DIVU,
    OPCODE_DIVUI,
    OPCODE_DIVUQ,
    OPCODE_AND,
    OPCODE_ANDI,
    OPCODE_ANDQ,
    OPCODE_OR,
    OPCODE_ORI,
    OPCODE_ORQ,
    OPCODE_XOR,
    OPCODE_XORI,
    OPCODE_XORQ,
    OPCODE_ASL,
    OPCODE_ASLI,
    OPCODE_ASLQ,
    OPCODE_LSL,
    OPCODE_LSLI,
    OPCODE_LSLQ,
    OPCODE_ASR,
    OPCODE_ASRI,
    OPCODE_ASRQ,
    OPCODE_LSR,
    OPCODE_LSRI,
    OPCODE_LSRQ,

    //BRU
    OPCODE_BNE,
    OPCODE_BEQ,
    OPCODE_BL,
    OPCODE_BLE,
    OPCODE_BG,
    OPCODE_BGE,
    OPCODE_BLS,
    OPCODE_BLES,
    OPCODE_BGS,
    OPCODE_BGES,
    OPCODE_CMP,
    OPCODE_CMPI,
    OPCODE_FCMP,
    OPCODE_FCMPI,
    OPCODE_DCMP,
    OPCODE_DCMPI,
    OPCODE_JMP,
    OPCODE_CALL,
    OPCODE_JMPR,
    OPCODE_CALLR,
    OPCODE_RET,
} Opcode;

#define MAX_OPERANDS 3

typedef struct Operation
{
    Opcode op; //< the op code
    uint32_t operands[MAX_OPERANDS]; //< either register or immediate values
    uint32_t size; //< 0 = byte, 1 = word, 2 = doubleword, 3 = quadword
    uint32_t data; //< additionnal data, op dependent
} Operation;

#define DSRAM_SIZE  (128u * 1024u)
#define ISRAM_SIZE  (128u * 1024u)
#define CACHE_SIZE  (32u * 1024u)
#define IOSRAM_SIZE (256u)
#define IREG_COUNT  (64u)
#define FREG_COUNT  (128u)
#define MAX_OPCODE  (4u)

#define XCHG_MASK (0x01u)
#define Z_MASK (0x02u)
#define S_MASK (0x04u)
#define U_MASK (0x08u)
#define R_MASK (0x03FFF0u)

typedef struct ArProcessor_T
{
    ArProcessor next;
    ArVirtualMachine parent;

    uint8_t dsram [DSRAM_SIZE];
    uint8_t isram [ISRAM_SIZE];
    uint8_t cache [CACHE_SIZE];
    uint8_t iosram[IOSRAM_SIZE];

    uint64_t ireg[IREG_COUNT];
    uint64_t freg[FREG_COUNT / 2u];

    uint32_t pc; //program-counter
    uint32_t opcodes[MAX_OPCODE];

    /// \brief CPU Flags register
    ///
    /// Bit 0: XCHG flag, 1 is 4-way decode, 0 is 2-way
    /// Bit 1: Z flag, 1 if not equal, 0 if equal
    /// Bit 2: S flag, 1 if lesser, 0 if greater (signed comparison)
    /// Bit 3: U flag, 1 if lesser, 0 if greater (unsigned comparison)
    /// Bit 4-17: R value, the PC address of the last call
    uint32_t flags;

    Operation operations[MAX_OPCODE];
    uint32_t delayedBits;
    Operation delayed[MAX_OPCODE];
    uint32_t dma; //1 if dmaOperation is to be treated
    Operation dmaOperation;

} ArProcessor_T;

typedef struct Vector4f
{
    float x;
    float y;
    float z;
    float w;
} Vector4f;

typedef struct ArPhysicalMemory_T
{
    ArVirtualMachine parent;

    uint8_t* memory;
    size_t size;

} ArPhysicalMemory_T;

#endif
