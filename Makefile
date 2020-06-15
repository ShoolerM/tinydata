CC = gcc
CFLAGS = -g -Wall
DEPS = ram.h tools.h functions.h

SRC := src


ODIR = objects
_OBJ = main.o ram.o tools.o functions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS = -lwiringPi


$(ODIR)/%.o: $(SRC)/%.c $(SRC)/$(DEPS)
	mkdir -p objects
	$(CC) $(CFLAGS) -c $< -o $@


test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
