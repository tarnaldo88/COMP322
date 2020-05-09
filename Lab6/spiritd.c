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

static pid_t mole1;
static pid_t mole2;
static int var;

void randMole();
static void sigHandler(int signum);
void spirit();

int main(int argc, char **argv){
    spirit();
    return EXIT_SUCCESS;
}

void spirit(){
    pid_t dPID;
    pid_t sid;
    if ((dPID = fork()) < 0){
        fprintf(stderr, "Error: fork has failed\n");
    }
    if (dPID != 0){        
        printf("Daemon PID: %d\n", dPID);
        exit(0); //parent is killed, daemon will run in background
    }
    if (dPID == 0) {
        signal(SIGTERM, sigHandler);
        signal(SIGUSR1, sigHandler);
        signal(SIGUSR2, sigHandler);
        //Change file permissions of daemon
        umask(0); 
        if ((sid = setsid()) < 0){
            fprintf(stderr, "setsid() failed\n");
        }
        int fd1 = open("/dev/null", O_RDONLY);
        //changes the directory to root
        if (chdir("/") != 0){ 
            fprintf(stderr, "Error: chdir() has failed\n");
        }
        if (fd1 < 0){
            fprintf(stderr, "Error: log has failed to open\n");
        }
        //redirecting stdout to the log file
        if (dup2(fd1, STDOUT_FILENO) < 0){
            fprintf(stderr, "Error: STDOUT failed to redirect\n");
        }
        //redirecting stderr to the log file
        if (dup2(fd1, STDERR_FILENO) < 0){
            fprintf(stderr, "Error: STDERR failed to redirect\n");
        }
        if (dup2(fd1, STDIN_FILENO) < 0){
            fprintf(stderr, "Error: STDIN failed to redirect\n");
        }
        close(fd1);
        while (1){
            sleep(1);
        }
    }
}

static void sigHandler(int sig){
    if(sig == SIGTERM){
        kill(mole2, SIGTERM);
        kill(mole1, SIGTERM);
        exit(0);
    } else if(sig == SIGUSR2){
        randMole();
        (void) signal(SIGUSR2, sigHandler);
    } else if(sig == SIGUSR1){
        randMole();
        (void) signal(SIGUSR1, sigHandler);
    }
}

void randMole(){
    char moleNum[30];
    int var = rand() % 2;
    sprintf(moleNum, "%d", var + 1);
    char * mArgv[] = {"mole", moleNum, 0};
    if (moleNum == 0){
        if (kill(mole1, SIGCHLD) < 0){
            fprintf(stderr, "Process already killed");
        }
        mole1 = fork();
        if (mole1 == 0) {
            execv(mArgv[0], mArgv);
        } else {
            if (kill(mole2, SIGCHLD) < 0){
                fprintf(stderr, "Process already killed");
            }
            mole2 = fork();
            if (mole2 == 0){
                execv(mArgv[0], mArgv);
            }
        }
    }
}