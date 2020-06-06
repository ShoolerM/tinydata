CC = gcc
CFLAGS = -g -Wall -o
ODIR = objects
DEPS = globals.h

_OBJ = globals.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS = -lwiringPi

$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p objects
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
