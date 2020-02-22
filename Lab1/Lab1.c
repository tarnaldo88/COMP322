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
    printf("PPID: %d, ", pid);
    printf("PID: $d\n", ppid);
}

void parentPids(pid_t pid, pid_t ppid, pid_t cpid, int status) {
    printf("PPID: %d, ", ppid);
    printf("PID: $d, CPID: %d, RETVAL: %d", getpid, cpid, WIFEXITED(status));
}

void timesChild(clock_t userTime, clock_t sysTime){
    printf("CUSER: %d,CSYS: %d", (int)userTime, (int)sysTime);
}

void timesParent(clock_t userTime, clock_t sysTime){
    printf("CUSER: %d, CSYS: %d\n", (int)userTime, (int)sysTime);

}

int main() {
    time_t seconds = time(NULL);
    printf("START: %ld\n", seconds);
    pid_t pid, ppid, pWait;
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
        timesChild(clocks.tms_utime, clocks.tms_stime);
        timesParent(clocks.cutime, clocks.cstime);
    }
    printf("\nSTOP: %d", time(NULL));
    return 0;
}