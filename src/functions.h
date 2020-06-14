#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include "ram.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void AssembleFile(FILE* fp);
void nop(MemoryTracker* memTracker);
void lda(MemoryTracker* memTracker);
void add(MemoryTracker* memTracker);
void sub(MemoryTracker* memTracker);
void sta(MemoryTracker* memTracker);
void ldi(MemoryTracker* memTracker);
void jmp(MemoryTracker* memTracker);
void jc(MemoryTracker* memTracker);
void jz(MemoryTracker* memTracker);
void addi(MemoryTracker* memTracker);
void subi(MemoryTracker* memTracker);
void dsp(MemoryTracker* memTracker);
void prnt(MemoryTracker* memTracker);
void halt(MemoryTracker* memTracker);
void printa(MemoryTracker* memTracker);


#endif
