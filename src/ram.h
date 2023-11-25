#ifndef _RAM_H
#define _RAM_H

#include <inttypes.h>


//PINs are denoted as to their position from the top of the left hand row of the GPIO pins
#define RUN 8 //PIN 2
//Prog is apparently active LOW, get creative
#define PROG 9 //PIN 3
#define WRITE 7 //PIN 4
#define STEP 3 //NA
#define CLOCK_START 0 //PIN 6
#define CLOCK_STOP  2 //PIN 7

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
void stepProgram();
void setAllPins();
void setMAR(int value);
void writeRAM(int value);
#endif
