#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "functions.h"
#include "ram.h"
#include "tools.h"

void AssembleFile(FILE* fp)
{
    //MemoryTracker* mt = InitMemoryTracker();

    int* lines = (int*) calloc(255, sizeof(int*));
    int numLines = GetLines(fp, lines);
    char state = 0;
    for(int i=0; i<numLines; i++)
    {
        switch(state)
        {
            case(0):
                setMAR(lines[i]);
                state = 1;
            case(1):
                writeRAM(lines[i]);
                state = 0;
        }
    }

}

/*
void nop(MemoryTracker* memTracker)
{
    writeOut(memTracker, 0);
}

void lda(MemoryTracker* memTracker)
{
    writeOut(memTracker, 1);
}

void add(MemoryTracker* memTracker)
{
    writeOut(memTracker, 2);
}

void sub(MemoryTracker* memTracker)
{
    writeOut(memTracker, 3);
}

void sta(MemoryTracker* memTracker)
{
    writeOut(memTracker, 4);
}

void ldi(MemoryTracker* memTracker)
{
    writeOut(memTracker, 5);
}

void jmp(MemoryTracker* memTracker)
{
    writeOut(memTracker, 6);
}

void jc(MemoryTracker* memTracker)
{
    writeOut(memTracker, 7);
}

void jz(MemoryTracker* memTracker)
{
    writeOut(memTracker, 8);
}

void addi(MemoryTracker* memTracker)
{
    writeOut(memTracker, 9);
}

void subi(MemoryTracker* memTracker)
{
    writeOut(memTracker, 10);
}

void dsp(MemoryTracker* memTracker)
{
    writeOut(memTracker, 12);
}

void prnt(MemoryTracker* memTracker)
{
    writeOut(memTracker, 13);
}

void halt(MemoryTracker* memTracker)
{
    writeOut(memTracker, 14);
}

void prnta(MemoryTracker* memTracker)
{
    writeOut(memTracker, 15);
}
*/
