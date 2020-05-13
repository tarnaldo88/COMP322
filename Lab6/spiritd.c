/*
Programmer: Arnaldo Torres
Due Date: 5/8/20
Program spiritd (LAB6):program that is intended to run as a daemon, 
and based upon signals will either create or destroy child processes.
*/
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/resource.h>

static pid_t mole;
static pid_t mole2;
static int var;

static void sigHandler(int signum);
void spirit();
void fdAndSigCatcher();
void fileLimits();

int main(int argc, char **argv){
    spirit();
    return EXIT_SUCCESS;
}

static void sigHandler(int sig){
    char varChARzard[10];
    //made to ease passing arguments, instead of a separate declaration for each
    char *shortcut[]={"mole",varChARzard,0};

    if(sig == SIGTERM){
        kill(mole2, SIGTERM);        
        fprintf(stderr,"terminate %d\n", (int)mole2);
        printf("End Daemon\n");
        exit(0);
    } else if(sig == SIGUSR2){
        //code for dealing with sig 1 or sig 2 is practically the same but with minor differences
        if(var == 1){
            fprintf(stderr,"SIGCHLD sent to %d\n",(int)mole2);
            kill(mole2,SIGCHLD);
        }
        var = rand() % 2;        
        sprintf(varChARzard,"%d",var+1);

        mole2 = fork();

        if(mole2  == 0){
        fprintf(stderr,"Executing: %s , %s\n",shortcut[0],shortcut[1]);
        execv(shortcut[0],shortcut);
        fprintf(stderr,"Error: failed to execute, %s , %s\n",shortcut[0],shortcut[1]);
        }
        signal(SIGUSR1,sigHandler);
    } else if(sig == SIGUSR1){
        if(var==0 && mole2 > 0) {
            fprintf(stderr,"SIGCHLD sent to %d\n",(int)mole2);
            kill(mole2,SIGCHLD);
        }
        var=rand()%2;
        sprintf(varChARzard,"%d",var+1);

        mole2 = fork();
        
        if(mole2 == 0){
            fprintf(stderr,"Executing: %s , %s\n",shortcut[0],shortcut[1]);
            execv(shortcut[0],shortcut);
            fprintf(stderr,"Error: failed to execute, %s , %s\n",shortcut[0],shortcut[1]);
        }
        signal(SIGUSR1,sigHandler);
    } else {
        printf(stderr,"Unknown signal\n");
    }
}

void spirit(){
    char varChARzard[2];
    char * shortcut[]={"mole",varChARzard,0};    
    pid_t sessionId;
    mole = fork();
    //check to ensure fork did not fail
    if(mole < 0){
        fprintf(stderr,"Error: unable to fork \n");
    }
    if(mole > 0){
        fprintf(stderr,"Mole PID: %d\n",mole);
        exit(EXIT_FAILURE);
    }
    umask(0);
    //have to start a new session, then check that it did not fail
    sessionId = setsid();
    if(sessionId < 0){
        fprintf(stderr,"Error: failed to start new session\n");
        exit(EXIT_FAILURE);
    }
    fileLimits();
    fdAndSigCatcher();
    //fork the child, aka mole2
    mole2 = fork();

    while(1){
        sleep(1);
        if(mole2 == 0){
            var=rand()%2;
        }
        //takes in either mole 1 or 2 and also casts var as char, hence the new pokemon, varCHARzard
        sprintf(varChARzard,"%d",var+1);        
        printf("kill child process: %s\n ",shortcut[1]);
        execv(shortcut[0],shortcut);
        printf(stderr,"Error: unable to kill child process %s",shortcut[1]);
    }
}

void fileLimits(){
    struct rlimit rLimit;
    int i = 0;
    //check that file limits are found, and then if condition to set max
    if(getrlimit(RLIMIT_NOFILE,&rLimit)<0){
        fprintf(stderr,"Error: unable to find file limits\n");
    }
    if(rLimit.rlim_max == RLIM_INFINITY){
        rLimit.rlim_max = 1024;
    }
    //for loop to close fd's
    for(; i < rLimit.rlim_max; i++){
        close(i);
    }
}

void fdAndSigCatcher(){
    int fd,fd1,fd2;
        /* 
    Assign values to the file descriptors, and their numbers correlate to what fucntion they will serve
    0 : STDIN
    1 : STDOUT
    2 : STDERR
    */
    fd = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    //set signal catch for signal termination, and the user defined signals 1 and 2
    signal(SIGTERM, sigHandler);
    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2,sigHandler);    
}