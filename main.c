#include <stdio.h>
#include <wiringPi.h>
#include "globals.h"

int main(void)
{
    printf("Lets flash an LED!\n");
    wiringPiSetup();
    initPins();
    setAllPins(LOW);

    writeMAR(5);
    writeRAM(0xff);
    delay(1000);
    writeMAR(0);
    delay(1000);
    writeMAR(5);
    return 0;
}
