/*
Programmer: Arnaldo Torres
Due Date: 3/23/20
Program: Catcher
a program that catches a number of predefined signals, 
and prints status information on stdout.
*/
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h> 
//#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h>

void sigHand(int sig);
void catcher(int argc, char **argv);
static int count = 0, termCount = 0; //how many signals have been caught
static const char signals [31][16] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "KILL"
                                  "USR1", "EGV", "USR2", "PIPE", "ALRM", "TERM", "CHLD", "CONT", "STOP"
                                  "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF"
                                  "WINCH", "IO", "PWR", "SYS", "TMIN"};    

int main(int argc, char ** argv){    
    catcher(argc, argv);
    return 0;
}

void catcher(int argc, char **argv) {
    int i,x,arrSize;
    char catchThis[38];
    fprintf(stderr, "catcher: $$ = %d\n", getpid());   

    for (i = 1; i < argc; i++){
        for(x = 0; x < 31; x++){
            if(strcmp(argv[i],signals[x]) == 0 ){
                signal(x+1, sigHand);
                printf("%s was found and needs to be caught\n", signals[x]);
            }            
        }
    } 
    pause();
    fprintf(stderr, "catcher: Total signals count = %d\n", count); 
}

void sigHand(int sig){
    time_t seconds;
    time(&seconds);
    if(sig == 15){
        termCount++;
    } else{
        termCount = 0;
    }
    count++;
    printf(" SIG%s caught at %ld\n", signals[sig-1], seconds); 
}