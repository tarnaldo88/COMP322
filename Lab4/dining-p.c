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
#include <sys/types.h>
#include <sys/wait.h>

void termHandler(int sig);
void progCheck(int pos, int seats, int argc);
void deallocate(char semName1[], char semName2[], sem_t* chop[]);
void dining(int argc, char **argv);
void eating(int pos);
void thinking(int pos);

static int end = 0; //value to know when to end dining loop

int main(int argc, char **argv){
  dining(argc, argv);
  return EXIT_SUCCESS;
}

//handles SIGTERM, and flips switch to end loop and end program
void sigHandler(int sig) {
	signal(SIGTERM, sigHandler);
    printf("SIGTERM(%d) processed\n", sig);
	end = 1;
}

void dining(int argc, char **argv){
    //keep track of the eat and think cycles
    int cycle = 0, i = 0, semVal1, semVal2;
    int pos = atoi(argv[2]);
	int seats = atoi(argv[1]);
	sem_t * chop[2];
	sem_t * rtn1;
	sem_t * rtn2;
	char name[50], semName1[50], semName2[50]; //50 as an arbitrary number so nothing too random can overflow 

	progCheck(pos,seats,argc);
    signal(SIGTERM, sigHandler);
	
	if(seats != 1){
		sprintf(name, "%d", (pos % seats));
	} else if (seats == 1){
		sprintf(name, "%d", (pos+ 1));
	}

	strcpy(semName1, "/");
	strcat(semName1, argv[2]);

	strcpy(semName2, "/");
	strcat(semName2, name);
	
    //start the left semaphore
    rtn1 = sem_open(semName1, O_CREAT | O_EXCL, 0666, 1);
	if(rtn1 == SEM_FAILED){
		rtn1 = sem_open(semName1, 0);
	}
	//start the right semaphore
	rtn2 = sem_open(semName2, O_CREAT | O_EXCL, 0666, 1);
	if(rtn2 == SEM_FAILED){
		rtn2 = sem_open(semName2, 0);
	}
	chop[0] = rtn1;
	chop[1] = rtn2;

    if(setpgid(getpid(), getppid()) != 0){
		printf("Unable to get group id\n");
		exit(EXIT_SUCCESS);
	}

    //philosphers start dining
	do {
		think(pos);
		sem_getvalue(chop[1], &semVal1);
		sem_getvalue(chop[0], &semVal2);

		//determine if left or right is free to go eat
		if(semVal1 == 1 && semVal2 == 1){

			eat(pos);
		//eating completed, post that eating is done
			sem_post(chop[1]);
			sem_post(chop[0]);
		} else{
			//wait for a free spot
			sem_wait(chop[0]);
			sem_wait(chop[1]);
		}
        cycle++;
	} while (!end);

    deallocate(semName1,semName2,chop);
    fprintf(stderr, "Philosopher #%d completed %d cycles.\n", pos, cycle);
}

void progCheck(int pos, int seats, int argc){
	//check there are at least 2 arguments
	if(argc != 3){
		printf("Error: arguments < 2 \n");
		exit(EXIT_FAILURE);
	} else if(!(pos <= seats)){ //make sure enough spots at the table
		printf("Philosopher %d rejected due to table full\n", pos);
		exit(EXIT_FAILURE);
	}	
}

void eating(int var){
	printf("Philosopher #%d is eating\n", var);	
	usleep(rand() % 888888);
}
void thinking(int var){
	printf("Philosopher #%d is thinking\n", var);
	usleep(rand() % 888888);
}

//remove philospher from eat/think cycle and deallocate system resources
void deallocate(char semName1[], char semName2[], sem_t* chop[]){
	sem_close(chop[0]);
	sem_close(chop[1]);

	sem_unlink(semName1);
	sem_unlink(semName2);

	sem_destroy(chop[0]);
	sem_destroy(chop[1]);
}