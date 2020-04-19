/*
Programmer: Arnaldo Torres
4/20/20

Description: a program that simulates a single dining philosopher.  
The program is designed to be executed numerous times, simultaneously, to demonstrate the effect use of semaphores.
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

void termHandler(int sig);
void dining(int argc, char **argv);
void eat(int var);
void thinking (int var);

int main(int argc, char **argv) {
  dining(argc, argv);
  return 0;
}

void sigHandler(int sig) {
	fprintf(stderr, "Philosopher #%d completed %d cycles\n", pNum, numCycles);
	exit(EXIT_SUCCESS);
}

void dining(int argc, char **argv) {
	sem_t chop[5];
	signal(SIGTERM, sigHandler);

	do {
		wait(chop[i]);
		wait(chop[(i + 1) % 5]);

		signal(chop[i]);
		signal(chop[(i + 1) % 5]);
	} while (true);
}

void eat(int var) {
	printf("Philosopher #%d is eating\n", var);	
	usleep(rand());
}

void think(int var) {
	printf("Philosopher #%d is thinking\n", var);
	usleep(rand());
}