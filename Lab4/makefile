#Arnaldo Torres Makefile
# Lab4: Rice^3

EXEC=dining-p launch-philosophers
SRC=dining-p.c
OBJ=dining-p.o
SRC2 = launch-philosophers.sh

CC=gcc
CFLAGS=-g

all: $(EXEC)

$(EXEC):

launch-philosophers:

	chmod +x &(SRC2)

dining-p:

	$(CC) $(CFLAGS) -c $(SRC) ${-lpthread -lrt} -Wall -Wextra
	$(CC) $(CFLAGS) -o $(OBJ) ${-lpthread -lrt}

CLEAN:
		rm -f $(EXEC) $(OBJ) *~
