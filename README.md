# SATIUS
## A simple, better VM

Satius is designed as a base for a replacement
of languages such as python in my own use at
school.

It has the 4 8 bit registers + the stack register
instruction pointer and the base pointer.

It also has two 8 bit registers and a 16 bit register

they are as follows:

- A  : 64
- B  : 64
- C  : 64
- D  : 64

- L  :  8
- H  :  8
- X  : 16

- SP : 64
- BP : 64
- IP : 64

X overlaps with the lower half of D
L overlaps with the lower low quarter of C
H overlaps with the lower high quarter of C

There are the following instructions:

- 00000000 : `NOP        `
- 10000000 : `LDI R64 I64`
- 01000000 : `LDX I16    `
- 11000000 : `LD8  R8  I8`
- 00100000 : `ADD R64 R64`
- 10100000 : `ADX I16    `
- 01100000 : `ADX  R8    `
- 11100000 : `AD8  R8  R8`
- 00010000 : `SUB R64 R64`
- 10010000 : `SBX I16    `
- 01010000 : `SBX  R8    `
- 11010000 : `SB8  R8  R8`
- 00110000 : `AND R64 R64`
- 10110000 : `ANX I16    `
- 01110000 : `ANX  R8    `
- 11110000 : `AN8  R8  R8`
- 00010000 : `OR  R64 R64`
- 10010000 : `ORX I16    `
- 01010000 : `ORX  R8    `
- 11010000 : `OR8  R8  R8`
- 00110000 : `NOT R64    `
- 10110000 : `NTX        `
- 01110000 : `NT8  R8    `
- 11110000 : `CON R64 I64`
- 00001000 : `CNX I64    `
- 10001000 : `CN8  R8 I64`
- 01001000 : `TRN R64 R64`
- 11001000 : `TRN R64   X`
- 00101000 : `TRX  R8    `
- 10101000 : `TR8  R8  R8`
- 01101000 : `PRN      R8`
- 11101000 : `INP      R8`
- 00011000 : `PUS R64    `
- 10011000 : `POP R64    `
- 01011000 : `STR R64 M64`
- 11011000 : `STX M64    `
- 00111000 : `ST8  R8 M64`
- 10111000 : `LDM R64 M64`
- 01111000 : `LMX M64    `
- 11111000 : `LM8  R8 M64`
- 00000100 : `JUN I64    `



