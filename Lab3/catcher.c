/*
Programmer: Arnaldo Torres
Due Date: 3/23/20
Program: Catcher
a program that catches a number of predefined signals, and prints status information on stdout.

*/

#include <signal.h>
#include <sys/types.h>
#include <errno.h> 
//#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h>

#define SIGUSR1 10
#define SIGUSR2 12

void sigHand(int sig);
void catcher(int argc, char **argv, int count, int sigCount);

int main(int argc, char ** argv){
    static int sigCount= 0, count = 0; // sigCount times SIGTERM is caught;  count = total signals
    catcher(argc,argv, count, sigCount);
    return 0;
}

void catcher(int argc, char **argv, int count, int sigCount) {
    int i;
    fprintf(stderr, "catcher: $$ = %d\n", getpid());    

    for( i = 0; i < argc; i++){
        //pause();
        signal(*argv[i], sigHand);
        count++;
    }

    if (signal(SIGINT,sigHand) == SIG_ERR){
            //error wasnt able to intrepret signal
             exit(EXIT_FAILURE); 
        }      

    fprintf(stderr, "catcher: Total signals count = %d\n", count); 
}

void sigHand(int sig){
    time_t seconds;
    time(&seconds);
    char * signals[] = {"SIGTERM", "SIGUSR1", "SIGUSR2"};

    if (sig == SIGUSR1){
        printf("%s caught at : %ld\n", signals[1], seconds);  
    } else if (sig == SIGUSR2){
        printf("%s caught at : %ld\n", signals[2], seconds);  
    } else if(sig == SIGTERM){
        printf("%s caught at : %ld\n", signals[0], seconds);
        
    }
    /*
    int i = 1;
    printf("inside sigHand\n");
    for (;i < argc; i++) {
        if (sig == argv[i]){
            printf("%s caught at : %ld\n", argv[i], seconds);            
        }
    }
    */
}