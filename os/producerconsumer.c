#include "stdio.h"
#include "sys/mman.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "semaphore.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"

#define BUFFER_SIZE 10
#define handle_error(arg) { perror(arg); exit(EXIT_FAILURE); }

typedef struct {
	sem_t mutex;
	sem_t full;
	sem_t empty;
	int buffer[BUFFER_SIZE];
} shm;

// down = sem_wait
// up = sem_post

void produce(shm *ptr) {
	int n, i = 0;
	while (true) {
		sem_wait(&ptr->empty);
			sem_wait(&ptr->mutex);
				sem_getvalue(&ptr->full, &n);
				ptr->buffer[n] = ++i;
				printf("Produced %d\n", ptr->buffer[n]);
				usleep(100000);
			sem_post(&ptr->mutex);
		sem_post(&ptr->full);
	}
}

void consume(shm *ptr) {
	int n, item;
	while (true) {
		sem_wait(&ptr->full);
			sem_wait(&ptr->mutex);
				sem_getvalue(&ptr->full, &n);
				item = ptr->buffer[n];
				printf("Consumed %d\n", item);
				usleep(100000);
			sem_post(&ptr->mutex);
		sem_post(&ptr->empty);
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <producer/consumer>\n", argv[0]);
		return -1;
	}

	shm *ptr;
	int fd;

	fd = shm_open("/pc", O_CREAT | O_RDWR, 0777);
	if(fd == -1) handle_error("shm_open");
	
	ptr = mmap(NULL, sizeof(shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED) handle_error("mmap");

	if(strcmp(argv[1], "producer") == 0) {
		// PRODUCER
		sem_init(&ptr->mutex, 1, 1);
		sem_init(&ptr->empty, 1, BUFFER_SIZE);
		sem_init(&ptr->full, 1, 0);

		if(ftruncate(fd, sizeof(shm)) == -1) handle_error("ftruncate");

		produce(ptr);
	} 
	else if(strcmp(argv[1], "consumer") == 0) {
		// CONSUMER
		consume(ptr);
	}

	shm_unlink("/pc");
	close(fd);

	sem_destroy(&ptr->mutex);
	sem_destroy(&ptr->full);
	sem_destroy(&ptr->empty);
	munmap(ptr, sizeof(*ptr));
	return 0;
}
