#include <stdio.h>
#include <wiringPi.h>
#include <inttypes.h>
#include <string.h>
#include "tools.h"
#include "ram.h"
#include "functions.h"


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Please provide a file to assemble\n");
        return 0;
    }
    char* filename = argv[1];
    printf("Running %s\n", filename);
    FILE* file = GetFile(filename);
    int* lines = (int*) calloc(255, sizeof(int*));
    int numLines = GetLines(file, lines);
    char state = 0;
    initPins();
    setAllPins(LOW);
    for(int i=0; i<numLines; i++)
    {
        switch(state)
        {
            case(0):
                setMAR(lines[i]);
                state = 1;
                break;
            case(1):
                writeRAM(lines[i]);
                state = 0;
                break;
        }
    }
    setAllPins(LOW);
    printf("argv: %s\n", argv[2]);
    if(!strcmp(argv[1], "view")){
        printf("View Mode\n");
        viewMode();
    }
    else if(!strcmp(argv[2], "step")){
        printf("Step mode\n");
        stepProgram();
    }       
    else{
        printf("Running...\n");
        runProgram(0, atoi(argv[2]));
    }
    return 0;
}
