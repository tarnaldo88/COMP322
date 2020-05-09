CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -g
LIBS = -lrt

GEN_EXEC_NAME = matrix_gen
ADD_EXEC_NAME = matrix_add 
GEN_OBJ = matrix_gen.o
ADD_OBJ= matrix_add.o
GEN_SRC = matrix_gen.c
ADD_SRC = matrix_add.c

all: matrix_add matrix_gen 

matrix_add: $(ADD_OBJ)
	$(CC) $(CFLAGS) -o $(ADD_EXEC_NAME) $(ADD_OBJ) $(LIBS)
	rm $(ADD_OBJ)

matrix_gen: $(GEN_OBJ)
	$(CC) $(CFLAGS) -o $(GEN_EXEC_NAME) $(GEN_OBJ) $(LIBS)
	rm $(GEN_OBJ)

matrix_add.o: 
	$(CC) $(CFLAGS) -g -c $(ADD_SRC)

matrix_gen.o: 
	$(CC) $(CFLAGS) -g -c $(GEN_SRC)

clean:
	rm -f $(GEN_EXEC_NAME)
	rm -f $(ADD_EXEC_NAME)
	rm -f $(GEN_OBJ)
	rm -f $(ADD_OBJ)