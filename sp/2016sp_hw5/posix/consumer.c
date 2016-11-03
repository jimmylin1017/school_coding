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
#include <sys/mman.h>
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

	// need use gcc -lrt (-lrt has to in the end of gcc)
	if((shmid = shm_open("tmpfile",O_RDWR, 0666)) == -1)
	{
		DIE("shm_open");
	}

	// warning: implicit declaration of function ‘ftruncate’ [-Wimplicit-function-declaration] use gcc -D_XOPEN_SOURCE=500
	if((ftruncate(shmid, shmblocks * sizeof(packet))) == -1)
	{
		DIE("ftruncate");
	}

	if((shm = mmap(NULL, shmblocks * sizeof(packet), PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0)) == MAP_FAILED)
	{
		DIE("mmap");
	}

	DEBUG("producer start read\n");

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

	DEBUG("producer read finish\n");

	printf("Lost: %d datas\n", lostnum);

	if(munmap(shm, shmblocks * sizeof(packet)) == -1)
	{
		DIE("munmap");
	}

	if(close(shmid) == -1)
	{
		DIE("close");
	}

	return 0;
}