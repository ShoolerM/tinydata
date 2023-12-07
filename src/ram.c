#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

void viewMode()
{
    int address = 0;
    while(address < 256)
    {
        puts("Address: ");
        scanf("%d", &address);
        puts("\n");
        setMAR(address);
    }
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
    pinMode(HALT, OUTPUT);
    pinMode(RESET, OUTPUT);

    digitalWrite(RUN, LOW);
    digitalWrite(PROG, LOW);
    digitalWrite(WRITE, HIGH);
    digitalWrite(STEP, LOW);
    digitalWrite(HALT, LOW);
    digitalWrite(RESET, HIGH);
}

void runProgram(int state, int speed)
{
    
    setMAR(0);
    digitalWrite(PROG, HIGH);
    digitalWrite(RESET, LOW);
    pinMode(HALT, INPUT);
    printf("Speed: %d\n", speed);
    
    while(1)
    {
        usleep(speed*100);
        if(state == 1){
            state = 0;
            digitalWrite(RUN, LOW);
        }
        else{
            state = 1;
            digitalWrite(RUN, HIGH);
        }
        if (digitalRead(HALT)){
            printf("GOT HALT!\n");
            return;
        }
    }
}

void stepProgram(int speed)
{
    for(int i = 0; i<8; i++)
    {
        pinMode(mar_pins[i], INPUT);
        pinMode(ram_pins[i], INPUT);
    }
    setMAR(0);
    digitalWrite(PROG, HIGH);
    digitalWrite(RESET, LOW);
    pinMode(HALT, INPUT);
    printf("Pins set, getting ready to run...\n");
    char input[100];
    int state = 0;
    while(strcmp(input, "r\n"))
    {
        memset(input, 0, sizeof(input));
        fgets(input, sizeof(input), stdin);
        if (!strcmp(input, "DEBUG\n"))
            viewMode();
        printf("Half Step\n");
        if(state == 1){
            state = 0;
            digitalWrite(RUN, LOW);
        }
        else{
            state = 1;
            digitalWrite(RUN, HIGH);
        }
        if (digitalRead(HALT)){
            printf("GOT HALT!\n");
            return;
        }
    }
    printf("Done stepping, running...\n");
    runProgram(state, speed);
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
