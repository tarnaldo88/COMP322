/*
Programmer: Arnaldo Torres
COMP 322
3/4/20
Lab2: Launch-Tube
Overview:
In this lab, you will develop two programs.  The two programs are designed to be down in two parts. 
The first part is a program called “launch”, whereas the second part is a program called “tube”.  
You will also need to modify the original makefile to allow the Professor to build your two software 
programs.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>  // fork
#include <stdlib.h>
#include <sys/wait.h>

void launcher(pid_t proc);

int main(int argc, char *argv[]){
    pid_t pid;
    launcher(pid);    
    return 0;
}
//launch function, forks and launches program
void launcher(pid_t proc){
    int loc;
    proc = fork();

    if(pid == 0)
    {
        //if 0 then child proc
        execve(argv[1], argv + 1, NULL);
    } else if (pid == -1){
        //fork failed
        printf("Fork failed, error %d\n", errno);
        exit(EXIT_FAILURE);
    } else {
        //in parent process due to fork returning positive value
        printf(stderr, "%s: $$ = %d\n", argv[1], proc);
        waitpid(proc, &loc,0);
        printf(stderr, "%s: $? = %d \n", argv[1], loc);
    }
}