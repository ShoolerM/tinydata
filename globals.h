//Order is LSB -> MSB
//This will appear backwards on actual tiny data
char mar[8] = {16, 15, 1, 4, 5, 6, 11, 10};
char ram[8] = {25, 24, 23, 22, 21, 30, 14, 13};
char *mar_pins = mar;
char *ram_pins = ram;
#define RUN 8
//Prog is apparently active LOW, get creative
#define PROG 9
#define WRITE 7
#define STEP 3
#define CLOCK_START 0
#define CLOCK_STOP  2

void initPins();
void setAllPins();
void writeMAR(int value);
void writeRAM(int value);
