/*
Programmer: Arnaldo Torres
Due Date: 5/8/20
Lab7: Program to generate a matrix
*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <aio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

struct variables {
    int startTime;
    int size;
    int value;
    int blocks;
    int blockSize;      
};

void argCheck(int argc, char ** argv, struct variables * st);
void matrixValidation(int argc, char ** argv);
void aioInitialization(struct aiocb *controlBlock, off_t offset, size_t blockSize, int fd);
void matrixAdd(struct aiocb *controlBlock, struct variables *st);

int main(int argc, char ** argv){    
    matrixValidation(argc,argv);
    return EXIT_SUCCESS;
}

void argCheck(int argc, char ** argv, struct variables * st) {

    char * checkNumber;

    if (argc != 3){
        fprintf(stderr, "Error: need at least two arguments\n");
        exit(EXIT_FAILURE);
    }
    // checking size of the argument
    st->size = strtol(argv[1], &checkNumber, 10);
    st->blocks = strtol(argv[2], &checkNumber, 10);

    // the end pointer in strol allows us to check if it is valid    
    if (!(((checkNumber == argv[1]) || (*checkNumber != '\0')) == 0)){
        fprintf(stderr, "Error: the size of %s is not valid\n", argv[1]);
        exit(EXIT_FAILURE);
    }    
    if (!!(((checkNumber == argv[2]) || (*checkNumber != '\0')) == 0)){
        fprintf(stderr, "Error: the size of %s is not valid\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    //make sure blocks is divisible
    if (st->size % st->blocks){
        fprintf(stderr, "Error: size is not evenly divisble by blocks\n");
        exit(EXIT_FAILURE);
    }
}

void matrixValidation(int argc, char ** argv) {
    struct variables varStruct;
    struct aiocb last, current, next;
    argCheck(argc,argv,&varStruct);  //validate arguments before going further
    int i, totSize = ((varStruct.size)*(varStruct.size)*4);
    off_t bSize;

    //record starting time
    varStruct.startTime = time(NULL);
    //get random number for the matrix addition
    varStruct.value = rand() % 101;
    //get block size
    varStruct.blockSize = varStruct.size / varStruct.blocks;
    bSize = (varStruct.blockSize*4)*(varStruct.blockSize*4);      

    //setup the current struct for reading
    aioInitialization(&current, 0, bSize, STDIN_FILENO);

    //read first block
    aio_read(&current);
    while (aio_error(&current) == EINPROGRESS){}
    //call aoi return, as it is the general convention 
    aio_return(&current);

    //async begins and reads blocks of the square of block size squared
    for (i = bSize; i < totSize; i += bSize) {

        //start IO reading for next bloc
        aioInitialization(&next, i, bSize, STDIN_FILENO);
        
        //read next block
        aio_read(&next);
        while (aio_error(&next) == EINPROGRESS){}

        //add values
        matrixAdd(&current, &varStruct);

        //use memcpy to copy current block into the previous block
        memcpy(&last, &current, sizeof(struct aiocb));

        //setup last block to be written
        aioInitialization(&last, i, bSize, STDOUT_FILENO);

        //write last block
        aio_write(&last);        
        while (aio_error(&last) == EINPROGRESS){}
        //call aoi return, as it is the general convention
        aio_return(&last);
        
        //sync write
        aio_fsync(O_SYNC, &last);

        //use memcpy to write over the current block with the next block's contents
        memcpy(&current, &next, sizeof(struct aiocb));
    }

    //deal with last block
    matrixAdd(&current, &varStruct);

    //write to stdout
    aioInitialization(&current, i, bSize, STDOUT_FILENO);
    aio_write(&current);
    while (aio_error(&current) == EINPROGRESS){}
    aio_return(&current);
    aio_fsync(O_SYNC, &current);
}

//Function to setup the aoicb struct so that it can be passed to the various read/write/return operations
void aioInitialization(struct aiocb *controlBlock, off_t offset, size_t blockSize, int fd) {
   
    if(fd == STDIN_FILENO){
        //set aoicb to 0
        memset(controlBlock, 0, sizeof(struct aiocb));
        //setup the buffer for aoicb struct, read only
        controlBlock->aio_buf = malloc(blockSize);
    }
    //set priority to 0, since all controlBlocks are same priority
    controlBlock->aio_reqprio = 0;
    //caller can set the file descriptor
    controlBlock->aio_fildes = fd;
    //set how many bytes to read
    controlBlock->aio_nbytes = blockSize;
    //ternary if conditon to set offset
    controlBlock->aio_offset = (fd == STDIN_FILENO ? offset : 0);    
}

void matrixAdd(struct aiocb *controlBlock, struct variables *st) {

    unsigned int i = 0, num;
    char buffer[5];

    //read the aoicb buffer
    for (; i < controlBlock->aio_nbytes; i += 4) {

        //zero out the char array
        memset(buffer, '\0', 5);
        //we read four bytes at a time since that is the max value between -100 and 200
        memcpy(buffer, (void *)controlBlock->aio_buf+i, 4);

        //get the number from the buffer
        num = strtol(buffer, NULL, 10);
        num += st->value;

        //set the buffer to 0
        memset(buffer, '\0', 5);

        //write the number 
        sprintf(buffer, "%4d", num);

        //write bufer to aoi buffer
        memcpy((void *)controlBlock->aio_buf+i, buffer, 4);
    }
}