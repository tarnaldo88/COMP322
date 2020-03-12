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
#include <unistd.h>  
#include <stdlib.h>
#include <sys/wait.h>

void tube(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    tube(argc, argv);    
    return 0;
}

void tube(int argc, char *argv[]){
    int pipefd[2];
    pipe(pipefd);
    pid_t  proc = fork();

    if (proc == 0) {
        //if 0 then child proc
        execve(argv[1], argv + 1, NULL);
    } else if (proc == -1) {
        //fork failed
        printf("Fork failed, error %d\n", errno);
        exit(EXIT_FAILURE);
    } else {
        pid_t process_id2 = fork();
        if (process_id2 > 0)
        {
             fprintf(stderr, "%s: $$ = %d\n", argv[1], process_id);
             fprintf(stderr, "%s: $$ = %d\n", argv[4], process_id2);
        }
        else if (process_id2 == 0)
        
        {}
        {

        }
        /* When fork() returns a positive number, we are in the parent process
         (the fork return value is the PID of the newly created child process) */
         int stat_loc;
         fprintf(stderr, "%s: $$ = %d\n", argv[1], process_id);
         waitpid(process_id, &stat_loc, 0);
         fprintf(stderr, "%s: $? = %d\n", argv[1], stat_loc);
    
}