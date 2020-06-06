#include <stdio.h>
#include <wiringPi.h>
#include "globals.h"

void initPins()
{
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
    digitalWrite(WRITE, LOW);
    digitalWrite(STEP, LOW);
    digitalWrite(CLOCK_START, LOW);
    digitalWrite(CLOCK_STOP, HIGH);
}

void setAllPins(int state)
{
    for(int i = 0; i<8; i++)
    {
        digitalWrite(mar_pins[i], state);
        digitalWrite(ram_pins[i], state);
    }
}

void writeMAR(int value)
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
    digitalWrite(WRITE, LOW);
    for(int i=0; i<8; i++)
    {
        if((value >> i) & 1)
            digitalWrite(ram_pins[i], HIGH);
        else
            digitalWrite(ram_pins[i], LOW);
    }
    digitalWrite(WRITE, HIGH);
    digitalWrite(WRITE, LOW);
}
