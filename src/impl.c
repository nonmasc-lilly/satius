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
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t   read8(STATE *state) { return (state->reg[IP]+=1,  *(uint8_t*)(state->buffer.content+(state->reg[IP]-1))); }
uint16_t read16(STATE *state) { return (state->reg[IP]+=2, *(uint16_t*)(state->buffer.content+(state->reg[IP]-2))); }
uint64_t read64(STATE *state) { return (state->reg[IP]+=8, *(uint64_t*)(state->buffer.content+(state->reg[IP]-8))); }

uint8_t   get8(uint64_t adr, STATE *state) { return  *(uint8_t*)(state->buffer.content+adr); }
uint16_t get16(uint64_t adr, STATE *state) { return *(uint16_t*)(state->buffer.content+adr); }
uint64_t get64(uint64_t adr, STATE *state) { return *(uint64_t*)(state->buffer.content+adr); }

uint8_t   set8(uint64_t adr,  uint8_t val, STATE *state) {  *(uint8_t*)(state->buffer.content+adr) = val; }
uint16_t set16(uint64_t adr, uint16_t val, STATE *state) { *(uint16_t*)(state->buffer.content+adr) = val; }
uint64_t set64(uint64_t adr, uint64_t val, STATE *state) { *(uint64_t*)(state->buffer.content+adr) = val; }

void instruction(INSTRUCTION inst, STATE *state) {
    uint64_t arg[2];
    state->reg[IP]++;
    switch(inst) {
    case NOP: break;
    case LDI:
        arg[0] =  read8(state);
        arg[1] = read64(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        state->reg[arg[0]] = arg[1];
        break;
    case LDX:
        arg[0] = read16(state);
        state->X = arg[0];
        break;
    case LD8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->R8[arg[0]] = arg[1];
        break;
    case ADD:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] += state->reg[arg[1]];
        break;
    case ADX:
        arg[0] = read16(state);
        state->X += arg[0];
        break;
    case ADX8:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->X += state->R8[arg[0]];
        break;
    case AD8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER8_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] += state->R8[arg[1]];
        break;
    case SUB:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] -= state->reg[arg[1]];
        break;
    case SBX:
        arg[0] = read16(state);
        state->X -= arg[0];
        break;
    case SBX8:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->X -= state->R8[arg[0]];
        break;
    case SB8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER8_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] -= state->R8[arg[1]];
        break;
    case AND:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] &= state->reg[arg[1]];
        break;
    case ANX:
        arg[0] = read16(state);
        state->X &= arg[0];
        break;
    case ANX8:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->X &= state->R8[arg[0]];
        break;
    case AN8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER8_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] &= state->R8[arg[1]];
        break;
    case OR:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] |= state->reg[arg[1]];
        break;
    case ORX:
        arg[0] = read16(state);
        state->X |= arg[0];
        break;
    case ORX8:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->X |= state->R8[arg[0]];
        break;
    case OR8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER8_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] |= state->R8[arg[1]];
        break;
    case NOT:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        state->reg[arg[0]] = ~state->reg[arg[0]];
        break;
    case NTX:
        arg[0] = read16(state);
        state->X = ~state->X;
        break;
    case NT8:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->R8[arg[0]] = ~state->R8[arg[0]];
        break;
    case CON:
        arg[0] = read8(state);
        arg[1] = read64(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        if(state->reg[arg[0]]) state->reg[IP] = arg[1];
        break;
    case CNX:
        arg[0] = read64(state);
        if(state->X) state->reg[IP] = arg[0];
        break;
    case CN8:
        arg[0] = read8(state);
        arg[1] = read64(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        if(state->R8[arg[0]] != 0) state->reg[IP] = arg[1];
        break;
    case TRN:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] = state->reg[arg[1]];
        break;
    case TRNX:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        state->reg[arg[0]] = state->X;
        break;
    case TRX:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->X = state->R8[arg[0]];
        break;
    case TR8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER8_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] = state->R8[arg[1]];
        break;
    case PRN:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        putc(state->R8[arg[0]], stdout);
        break;
    case INP:
        arg[0] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        state->R8[arg[0]] = getchar();
        break;
    case PUS:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        set64(state->reg[SP], arg[0], state);
        state->reg[SP] -= 8;
        break;
    case POP:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        get64(state->reg[SP], state);
        state->reg[SP] += 8;
        break;
    case STR:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        set64(state->reg[arg[1]], state->reg[arg[0]], state);
        break;
    case STX:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        set16(state->reg[arg[0]], state->X, state);
        break;
    case ST8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        set8(state->reg[arg[1]], state->R8[arg[0]], state);
        break;
    case LDM:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->reg[arg[0]] = get64(state->reg[arg[1]], state);
        break;
    case LMX:
        arg[0] = read8(state);
        REGISTER_CHECK(arg[0], state->reg[IP]);
        state->X = get16(state->reg[arg[1]], state);
        break;
    case LM8:
        arg[0] = read8(state);
        arg[1] = read8(state);
        REGISTER8_CHECK(arg[0], state->reg[IP]);
        REGISTER_CHECK(arg[1], state->reg[IP]);
        state->R8[arg[0]] = get8(state->reg[arg[1]], state);
        break;
    case JUN:
        arg[0] = read64(state);
        state->reg[IP] = arg[0];
        break;
    case HLT: state->halted = 1; break;
    default:
        printf("ERR: undefined instruction (%02x) at (IP=%d)", state->buffer.content[state->reg[IP]], state->reg[IP]);
        exit(1);
    }
}

void interpret(BUFFER buf) {
    STATE state;
    memset(&state, 0, sizeof(state));
    state.buffer.length = buf.length+STACK_SIZE+MEMORY_SIZE;
    state.buffer.content = malloc(state.buffer.length);
    memcpy(state.buffer.content+STACK_SIZE, buf.content, buf.length);
    state.reg[SP] = STACK_SIZE-1;
    state.reg[IP] = STACK_SIZE;
    while(!state.halted) {
        instruction(state.buffer.content[state.reg[IP]], &state);
    }
    free(state.buffer.content);
}
