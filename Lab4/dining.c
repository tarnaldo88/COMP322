/*
Programmer: Arnaldo Torres
4/20/20

Description: a program that simulates a single dining philosopher.  
The program is designed to be executed numerous times, simultaneously, to demonstrate the effect use of semaphores.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

void termHandler(int sig);
int randInt();
void dining(int argc, char **argv);
void eat(int pos);
void thinking (int pos);

static int end;
static int next;

int main(int argc, char **argv){
  dining(argc, argv);
  return 0;
}

void sigHandler(int sig) {
	signal(SIGTERM, sigHandler);
    printf("SIGTERM processed\n");
	end = 1;
}

void dining(int argc, char **argv){
    //first check there are at least 2 arguments
    if(argc != 3){
		printf("Error: arguments < 2 \n");
		exit(EXIT_FAILURE);
	}
	
    //keep track of the eat and think cycles
    int cycle = 0, i = 0;
    int pos = atoi(argv[2]);
	int seats = atoi(argv[1]);
	const int SIZE = seats * 32;
	sem_t chop[seats + 1];
	int shm_fd;
	char* sem = argv[2];

    signal(SIGTERM, sigHandler);
    setpgid();

    //check if there is room at the table
    if(!(pos <= seats)){
		printf("Philosopher %d rejected due to table full\n", position);
		exit(EXIT_FAILURE);
	}

    for(; i < seats; i++){	
		if(sem_init(&chop[i], 1, 1) < 0){
			printf("Error when initializing semaphore\n");
			exit(EXIT_FAILURE);
		}
	}

    shm_fd = shm_open(argv[2], O_CREAT | O_EXCL, 0666);

    if(shm_fd < 0){
		printf("Shared Memory Open failed\n");
		exit(EXIT_FAILURE);
	}
    
    mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); //memory map allocated

    //philosphers start dining
	do {
		sem_wait(&chop[pos]);
		sem_wait(&chop[(pos + 1) % seats]);
		eat(pos);

		sem_post(&chop[pos]);
		sem_post(&chop[(pos + 1) % seats]);
		think(pos);

        cycle++;
	} while (!end);

    kill_cycle(pos,chop,sem);
    fprintf(stderr, "Philosopher #%d completed %d cycles.\n", pos, cycle);
}

void eat(int var) {
	printf("Philosopher #%d is eating\n", var);	
	usleep(rand());
}

void think(int var) {
	printf("Philosopher #%d is thinking\n", var);
	usleep(rand());
}

//remove philospher from eat/think cycle and deallocate system resources
void kill_cycle(int position, sem_t chop[], char* sem)
{
	sem_close(&chop[position]);
	shm_unlink(sem);
	sem_destroy(&chop[position]);
}

int randInt(){

}