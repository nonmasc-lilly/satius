/*
*   satius, The better VM 
*   Copyright (C) 2024 Lilly H. St Claire
*
*            This program is free software: you can redistribute it and/or modify
*            it under the terms of the GNU General Public License as published by
*            the Free Software Foundation, either version 3 of the License, or (at
*            your option) any later version.
*
*            This program is distributed in the hope that it will be useful, but
*            WITHOUT ANY WARRANTY; without even the implied warranty of
*            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*            General Public License for more details.
*
*            You should have received a copy of the GNU General Public License
*            along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/

#ifndef __SATIUS_MAIN_H__
#define __SATIUS_MAIN_H__
#include <stdint.h>

typedef struct {
    uint8_t  *content;
    uint64_t   length;
} BUFFER;

typedef enum {
    A, B, C, D, BP, SP, IP, REGISTER_MAX,
    L=0, H=1, REGISTER8_MAX=2
} REGISTER;

typedef struct {
    uint8_t  halted, R8[2];
    uint16_t X;
    uint64_t reg[REGISTER_MAX];
    BUFFER   buffer;
} STATE;

typedef enum {
    NOP=0x00,
    LDI=0x01,            LDX=0x02,  LD8=0x03,
    ADD=0x04,            ADX=0x05, ADX8=0x06, AD8=0x07,
    SUB=0x08,            SBX=0x09, SBX8=0x0A, SB8=0x0B,
    AND=0x0C,            ANX=0x0D, ANX8=0x0E, AN8=0x0F,
     OR=0x10,            ORX=0x11, ORX8=0x12, OR8=0x13,
    NOT=0x14,            NTX=0x15,            NT8=0x16,
    CON=0x17,            CNX=0x18,            CN8=0x19,
    TRN=0x1A, TRNX=0x1B, TRX=0x1C,            TR8=0x1D,
    PRN=0x1E,            INP=0x1F,
    PUS=0x20,            POP=0x21,
    STR=0x22,            STX=0x23,            ST8=0x24,
    LDM=0x25,            LMX=0x26,            LM8=0x27,
    JUN=0x28,            HLT=0x29,
    INSTRUCTION_MAX
} INSTRUCTION;

#define REGISTER_CHECK(a, i) \
    do {if(a >= REGISTER_MAX) {printf("ERR: reg %d does not exist at (IP=%d)\n", a, i); exit(0);}} while(0)
#define REGISTER8_CHECK(a, i) \
    do {if(a >= REGISTER8_MAX) {printf("ERR: reg8 %d does not exist at (IP=%d)\n", a); exit(0);}} while(0)
#define STACK_SIZE 0xFFFF
#define MEMORY_SIZE 0xFFFFFF

uint8_t   read8(STATE *state);
uint16_t read16(STATE *state);
uint64_t read64(STATE *state);

void instruction(INSTRUCTION inst, STATE *state);
void interpret(BUFFER buf);

#endif
