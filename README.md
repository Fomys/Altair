# Altair
New computer and new CPU PoC

The main processor of the Altair K1 is a VLIW In Order CPU.  
It has 3 internal memory:  
128 KiB L1 data Scratchpad memory.  
128 KiB L1 instruction Scratchpad memory.  
32 KiB  L1 data cache (Direct mapped or Set-associative 2 ways).  
  
1 MiB L2 cache (Set-associative 2/4 ways).  
1 MiB L2 cache Scratchpad memory.  

The processor has no branch prediction, it will be based on the delay slot (1 cycle for Fetch) and 1 decode cycle + Jump (Delay)

He can also change the number of instructions with an swt instruction.  
Which allows you to switch to 2 or 4 instructions / cycle mode.  
all this to avoid too many "nop" and therefore not waste unnecessary space in the SRAM.

The goal of this processor is to reach the minimum of latency, and to solve the problem of latency of the RAM.  
For this, the compiler will have to do two things:  
- resolve pipeline conflicts  
- preload the data in advance with a DMA

This is a technique used on consoles like the Playstation 2 and 3, we have to make a double buffer, and therefore execute and read our data in buffer 1, while we preload our data in buffer 2.  
Then we execute the buffer 2 and we preload the buffer 1 and so on.

For floating point numbers in Altair , it will not be 100% compatible with the standard with IEEE 754  
-Non-normalized numbers are not handled (they are equal to zero).  
-Infinite numbers cannot be handled (they are worth the max value).  
-NaN values are not manage (they are worth the max value).  
-Rounding is always towards 0  
-Exceptions are not handled   

For the calculation unit it has:  
2ALU+2ALU(32 bits) 2VFPU 2LSU FDIV DIV BRU CMP  

If we are having trouble porting Linux to the Altair K1 thenwill have as main core (for the OS), a 64 bits RISC-V, scalar in order with an ALU/FPU/BRU/LSU,there will be no double float.  
32 KiB L1 data cache (Direct mapped or Set-associative 2 ways).  
32 KiB L1 instruction cache (Direct mapped or Set-associative 2 ways).  

The advantage of this processor is that it has a simple design, and requires little transistor for "high performance" and therefore consume / cost less than RISC Out Of Order processors.

### Todo list
- Finish the assembler program
- Make documentation (pdf / html) (ISA and hardware)
- Translate the IR code (Clang) for Altair
- Make the virtual machine

## Target configuration
Main core : RISC-V 2.5 GHz or Altair K1 2.5 GHz  
Sub  core : Altair K1 2.5 GHz , 6 cores   
LPDDR4 2666/3200 MHz , 8GB in a unified memory  
GPU Aldebaran G1 1 GHz , 4 CU , 1 TFlops  

## Link
Altair K1 ISA : https://docs.google.com/spreadsheets/d/1QSawEbuZwvMbYRcha7aj3VXp76EGc-zYoRJHNPjmhB8/edit?usp=sharing  

ALTAIR K1 Pipeline : https://docs.google.com/spreadsheets/d/1u-XBjAyq8LOzAFcWMXsdAChMMzbmTIuZtzWQ7XDTRdk/edit?usp=sharing  

ALTAIR IR ISA : https://docs.google.com/spreadsheets/d/19nOBbH_4KWaXxDSNA4JuZjaBble0VRrBxcVlEjTZ3iI/edit?usp=sharing  

ALTAIR Executable Header : https://docs.google.com/spreadsheets/d/1g7mEhaBIVBJ75-5gJ_TrYiVJVTZHEJQnqN0XXUBX57g/edit?usp=sharing

Aldebaran G1 ISA : https://docs.google.com/spreadsheets/d/1LiSZbdd6wCpa-sZZ9uLg5eAyGxdpMl363waUP927xS4/edit?usp=sharing  

GPU todo list : https://docs.google.com/spreadsheets/d/1eRX1vLHEJdrAsx2u1OiycSSz82G3cboVMcu8gBYkgGA/edit?usp=sharing  


## Pipeline
<img src="Pipeline4.png?raw=true" alt="Pipeline">

## Architecture intern 
<img src="arch_hard.png?raw=true" alt="arch">

## APU Die (700-900 MT) 40-50 mm² , 28 nm FD-SOI
<img src="APU.png?raw=true" alt="APU">


