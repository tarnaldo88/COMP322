/*
Programmer: Arnaldo Torres
Due date: 3/14/20
Lab2 Launch tube assignemnt
Launch program
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h>

void launcher(char *argv[]);

int main(int argc, char *argv[]){
    launcher(argv);
    return 0;
}

void launcher(char *argv[]){
    pid_t  pid = fork();

    if (pid == 0){
        //child process
        execve(argv[1], argv + 1, NULL);
    }
    else if (pid == -1){
        fprintf(stderr, "System was not able to fork. Error: %d\n", errno);
        exit(EXIT_FAILURE);        
    } else {
        //parent process
         int location;
         fprintf(stderr, "%s: $$ = %d\n", argv[1], pid);
         waitpid(pid, &location, 0);
         if(WIFEXITED(location) != 0){
           fprintf(stderr, "%s: $? = %d\n", argv[1], WEXITSTATUS(location));
         }
    }
}