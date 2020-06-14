#ifndef _RAM_H
#define _RAM_H

#include <inttypes.h>

#define RUN 8
//Prog is apparently active LOW, get creative
#define PROG 9
#define WRITE 7
#define STEP 3
#define CLOCK_START 0
#define CLOCK_STOP  2

typedef struct MemoryTracker
{
    uint8_t progLoc;
    uint8_t dataLoc;
    uint8_t labelLocations[256];
    char* labelNames[256];
    char* variableNames[256];
    uint8_t variableLocations[256];
    uint16_t variable;
}MemoryTracker;


MemoryTracker* InitMemoryTracker();
void writeData(MemoryTracker* memTracker);
void writeOut(MemoryTracker* memTracker, uint8_t opcode);
void initPins();
void runProgram();
void setAllPins();
void setMAR(int value);
void writeRAM(int value);
#endif
