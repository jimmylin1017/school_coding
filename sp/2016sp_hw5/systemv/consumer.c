#ifdef _DEBUG
  #define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
  #define DEBUG(format, args...)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define DIE(x) perror(x),exit(1)
#define MAX 5000
#define byte unsigned char

typedef struct packet
{
	int id;
	short dataShort[5];
	long dataLong[5];
	double dataDouble[5];
	byte dataByte[6];
} packet;


int main(int argc, char *argv[])
{
	int shmid, shmblocks, checknum[MAX] = {0}, lostnum = 0;
	packet *shm, tmp;
	key_t key;

	if(argc != 2)
	{
		printf("argument error!\n");
		exit(1);
	}

	shmblocks = atol(argv[1]);

	if(shmblocks > 30 || shmblocks < 5)
	{
		printf("shmblocks error please input 5~30!\n");
		exit(1);
	}

	if((key = ftok(".", 1)) == -1)
	{
		DIE("ftok");
	}

	if((shmid = shmget(key, shmblocks * sizeof(packet), IPC_CREAT | 0666)) == -1)
	{
		DIE("shmget");
	}

	if((shm = (packet *)shmat(shmid, NULL, 0)) == (void*)-1)
	{
		DIE("shmat");
	}

	DEBUG("consumer start read\n");

	tmp.id = 0;
	while(tmp.id < MAX-1)
	{
		for(int i = 0; i < shmblocks; i++)
		{
			memcpy(&tmp, shm + i, sizeof(packet));
			checknum[tmp.id] = 1;
		}
	}

	for(int i = 0; i < MAX; i++)
	{
		if(!checknum[i]) lostnum++;
	}

	DEBUG("consumer read finish\n");

	printf("Lost: %d datas\n", lostnum);

	if(shmdt(shm) == -1)
	{
		DIE("shmdt");
	}

	return 0;
}