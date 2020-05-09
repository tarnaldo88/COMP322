/*
Programmer: Arnaldo Torres
Due Date: 5/8/20
Lab7: Program to generate a matrix
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void matrixGen(int argc, char** argv);

int main(int argc, char** argv){
    matrixGen(argc,argv);
    return EXIT_SUCCESS;
}

void matrixGen(int argc, char** argv){
    int var, y = 0, x = 0, ret;
    int N = atoi(argv[1]);   

    if (argc != 2){
        fprintf(stderr, "Error: arguments invalid\n");
        exit(EXIT_FAILURE);
    }    
    for(; x < N; x++){
        for(; y < N; y++){
            fprintf(stdout, "%4d", (rand() % 101) * ((rand() % 2) ? 1 : -1));
        }
        printf("\n");
    }    
}