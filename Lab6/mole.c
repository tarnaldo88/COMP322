/*
Programmer: Arnaldo Torres
Due Date: 5/8/20
Program simply writes a signal line to a well-known log file (~/lab6.log)
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void mole(int argc, char **argv);

int main(int argc, char **argv) {
    mole(argc, argv);
    return 0;
}

void mole(int argc, char **argv){
    FILE *filep = fopen("lab6.log", "a");
    char *
    if (filep == NULL){
        fprintf(stderr, "Error: failed to create Lab log");
    }
    if (filep != 0){
        char * m;
        if (argc > 1 && strcmp(argv[1], "1") == 0){
            m = "Pop mole1";
        }else{
            m = "Pop mole2";
        }
        fclose(filep);
    }
}