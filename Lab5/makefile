#Arnaldo Torres
#Lab 5: Pages Makefile
#4/28/20

EXECUTABLE=lab5
SRC=lab5.c
OBJ=lab5.o

CC=gcc
CFLAGS=-g

all: $(EXECUTABLE)


$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

CLEAN:
	rm -f $(EXECUTABLE) $(OBJ) *~