EXEC-S=spiritd
EXEC-M=mole
SRC-S=spiritd.c
SRC-M=mole.c
OBJ-S=spiritd.o
OBJ-M=mole.o

CC=gcc
CFLAGS=-g

all: $(EXEC-S) $(EXEC-M)


$(EXEC-S): $(SRC-S)
	$(CC) $(CFLAGS) -c $(SRC-S)
	$(CC) $(CFLAGS) -o $@ $(OBJ-S)

$(EXEC-M): $(SRC-M)
	$(CC) $(CFLAGS) -c $(SRC-M)
	$(CC) $(CFLAGS) -o $@ $(OBJ-M)

clean:
	rm -f $(EXEC-S) $(EXEC-M) $(OBJ-S) $(OBJ-M) *~