#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "ram.h"

//Order is LSB -> MSB
//This will appear backwards on actual tiny data
char mar[8] = {16, 15, 1, 4, 5, 6, 11, 10};
char ram[8] = {25, 24, 23, 22, 21, 30, 14, 13};
char *mar_pins = mar;
char *ram_pins = ram;

MemoryTracker* InitMemoryTracker()
{
    MemoryTracker* mt = (MemoryTracker*)calloc(1, sizeof(MemoryTracker*));
    mt->progLoc = 0;
    mt->dataLoc = 0xff;
    mt->variable = 0;
    return mt;
}

void initPins()
{
    wiringPiSetup();
    for(int i = 0; i<8; i++)
    {
        pinMode(mar_pins[i], OUTPUT);
        digitalWrite(mar_pins[i], LOW);

        pinMode(ram_pins[i], OUTPUT);
        digitalWrite(ram_pins[i], LOW);
    }
    pinMode(RUN, OUTPUT);
    pinMode(PROG, OUTPUT);
    pinMode(WRITE, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(CLOCK_START, OUTPUT);
    pinMode(CLOCK_STOP, OUTPUT);

    digitalWrite(RUN, HIGH);
    digitalWrite(PROG, LOW);
    digitalWrite(WRITE, HIGH);
    digitalWrite(STEP, LOW);
    digitalWrite(CLOCK_START, LOW);
    digitalWrite(CLOCK_STOP, HIGH);
}

void runProgram()
{
    for(int i = 0; i<8; i++)
    {
        pinMode(mar_pins[i], INPUT);
        pinMode(ram_pins[i], INPUT);
    }
    digitalWrite(RUN, LOW);
    digitalWrite(PROG, HIGH);

}

void stepProgram()
{
    for(int i = 0; i<8; i++)
    {
        pinMode(mar_pins[i], INPUT);
        pinMode(ram_pins[i], INPUT);
    }
    digitalWrite(PROG, HIGH);
    digitalWrite(CLOCK_STOP, LOW);
    printf("Pins set, getting ready to run...\n");
    int stop;
    char input;
    while(input != 0x63)
    {
        printf("Half Step");
        input = getchar();
        digitalWrite(RUN, LOW);
        printf("Half Step");
        input = getchar();
        stop = digitalRead(CLOCK_STOP);
        digitalWrite(RUN, HIGH);
    }
    printf("Done stepping, running...\n");
    while(1)
    {
        digitalWrite(RUN, LOW);
        digitalWrite(RUN, HIGH);
    }
    printf("Clock Stop was set");
}

void setAllPins(int state)
{
    for(int i = 0; i<8; i++)
    {
        digitalWrite(mar_pins[i], state);
        digitalWrite(ram_pins[i], state);
    }
}

void setMAR(int value)
{
    for(int i=0; i<8; i++)
    {
        if((value >> i) & 1)
            digitalWrite(mar_pins[i], HIGH);
        else
            digitalWrite(mar_pins[i], LOW);
    }
}

void writeRAM(int value)
{
    digitalWrite(WRITE, HIGH);

    //Need to force PROG to be low so we can continue writing to RAM
    pinMode(PROG, OUTPUT);
    digitalWrite(PROG, LOW);
    for(int i=0; i<8; i++)
    {
        if((value >> i) & 1)
        {
            digitalWrite(ram_pins[i], HIGH);
        }
        else
        {
            digitalWrite(ram_pins[i], LOW);
        }
    }
    digitalWrite(WRITE, LOW);
    delay(20);
    digitalWrite(WRITE, HIGH);
}


void dataOut(MemoryTracker* memTracker)
{
    setMAR(memTracker->dataLoc);
    writeRAM(memTracker->variable);
    memTracker->dataLoc--;
}


void writeOut(MemoryTracker* memTracker, uint8_t opcode)
{
    setMAR(memTracker->progLoc);
    writeRAM(opcode);
    memTracker->progLoc++;
    if(memTracker->variable > 255)
        return;
    setMAR(memTracker->progLoc++);
    writeRAM(memTracker->variable);
    memTracker->progLoc++;
}
