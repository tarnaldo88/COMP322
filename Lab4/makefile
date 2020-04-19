##Arnaldo Torres Makefile Lab4 Dining
EXEC=dining-p
SRC=dining-p.c
OBJ=dining-p.o

CC=gcc
CFLAGS=-g

all: $(EXEC)

$(EXEC): $(SRC)
		$(CC) $(CFLAGS) -c $(SRC)
			$(CC) $(CFLAGS) -lpthread -o $@ $(OBJ)

CLEAN:
		rm -f $(EXEC) $(OBJ) *~
