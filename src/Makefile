CC = gcc
CFLAGS = -g -Wall
DEPS = ram.h tools.h functions.h

ODIR = objects
_OBJ = main.o ram.o tools.o functions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS = -lwiringPi


$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p objects
	$(CC) $(CFLAGS) -c $< -o $@


test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
