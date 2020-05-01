/*
Programmer: Arnaldo Torres
4/28/20
LAB 5: Page/Offset calculation
develop a single program that calculates the page number and the offset within the page for a given virtual memory address
*/
#include <stdlib.h>
#include <stdio.h>

int calculate(int argc, char **argv);
unsigned int pageNumber(int pSize, unsigned int address);
unsigned int offset(int pSize, unsigned int address);

void main(int argc, char **argv){    
    return calculate(argc,argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int calculate(int argc, char **argv){
    unsigned int address;
    const int pSize = 4096; // four kilobytes

    if (argc == 2){
        address = atoi(argv[1]);
        printf("The address %d contains:\n", address);		
		printf("page number = %d\n", pageNumber(pSize, address)); //prints page Number
        printf("offset = %d\n", offset(pSize, address)); // prints offset

        return 1;		
    } else {
        printf("Error: invalid number of arguments\n");
        return 0;
    }
}
unsigned int pageNumber(int pSize, unsigned int address){
    return address / pSize;
}
unsigned int offset(int pSize, unsigned int address){
    return address % pSize;
}