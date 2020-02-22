#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>  // fork
#include <stdlib.h>
#include <sys/wait.h>

void childPids(pid_t pid, pid_t ppid)
{
    printf("PPID: %d, ", (int)ppid);
    printf("PID: %d \n", (int)pid);
    exit(EXIT_SUCCESS);
}

void parentPids(pid_t pid, pid_t ppid, pid_t cpid, int status) {
    printf("PPID: %d, ", ppid);
    printf("PID: %d, CPID: %d, RETVAL: %d\n", pid, cpid, WIFEXITED(status));
}

void timesChild(clock_t userTime, clock_t sysTime){
    printf("USER: %d,SYS: %d \n", (int)userTime, (int)sysTime);
}

void timesParent(clock_t userTime, clock_t sysTime){
    printf("CUSER: %d, CSYS: %d", (int)userTime, (int)sysTime);

}

int main() {
    time_t seconds;
    time(&seconds);
    printf("START: %ld\n", seconds);
    pid_t pid, pWait;
    int status;

    pid = fork();
    struct tms clockTime;

    if(pid == -1){
        //there was an error exit with failure
        printf("error");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        //do child processes
        sleep(10);
        childPids(getpid(), getppid());
    } else if(pid > 0){
        pWait =  waitpid(pid,&status, 0);
        //do parent processes
        parentPids(getpid(), getppid(), pid, status);
        times(&clockTime);
        timesChild(clockTime.tms_utime, clockTime.tms_stime);
        timesParent(clockTime.tms_cutime, clockTime.tms_cstime);
    }
    time(&seconds);
    printf("\nSTOP: %ld\n", seconds);
    return 0;
}