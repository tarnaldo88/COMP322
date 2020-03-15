/* 
Programmer: Arnaldo Torres
Due date: 3/14/20
Lab2 Launch tube assignemnt
Tube program
*/
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h>

int main(int argc, char *argv[]){
     int pFileDesc[2];
    pipe(pFileDesc);
    int x = 0;
    int position;
    
    for(x = 0;x < argc;x++){
        if(strcmp(argv[x] , ",") == 0){
            argv[x] = NULL;
            position = x + 1;
            break;
        }
    }

    pid_t  pid = fork();

    if (pid == 0){    
        //child process because pid is 0 after fork    
        dup2(pFileDesc[1], 1);
        execve(argv[1], argv + 1, NULL);
    }
    else if (pid == -1)
    {
        //error in forking
        fprintf(stderr, "System was not able to fork. Error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    else
    {
        pid_t secondPid = fork();
        if (secondPid > 0)
        {
             fprintf(stderr, "%s: $$ = %d\n", argv[1], pid);
             fprintf(stderr, "%s: $$ = %d\n", argv[4], secondPid);
        }
        else if (secondPid == 0)
        {
            dup2(pFileDesc[0], 0);
            execve(argv[position], argv + position, NULL);
            exit(0);
        }
         close(pFileDesc[1]);
         close(pFileDesc[0]);        
         int location;
         int secLocation;
         waitpid(pid, &location, 0);
         waitpid(secondPid, &secLocation, 0);
         fprintf(stderr, "%s: $? = %d\n", argv[1], location);
         fprintf(stderr, "%s: $? = %d\n", argv[1], secLocation);
    }
    return 0;
}