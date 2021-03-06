#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// The following inclusions are important.
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;

	key = 9000;
	shmid = shmget (key, SHMSIZE, IPC_CREAT|0666);
	if (shmid < 0)
	{
		perror("key exist");
		exit(1);
	}

	shm = shmat(shmid, NULL, 0);
	
	if (shm == (char*)-1)
	{
		perror("shm retrieve failed");
		exit(1);
	}

	fprintf(stdout, "%s", shm);

	shm[0] = '*';

	shmdt(shm);

	return 0;

}
