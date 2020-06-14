#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* GetFile(char* filename)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    if(!fp)
        {
            printf("Failed to open File [%s], please try again\n", filename);
            return 0;
        }
    return fp;
}

int GetLines(FILE* fp, int* lines)
{
    int count = 0;
    while(!feof (fp))
    {
        fscanf(fp, "%d", &lines[count]);
        count++;
    }
    return count;
}
