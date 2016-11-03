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
	int shmid, shmblocks;
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
	if((shmid = shm_open("tmpfile",O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
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

	sleep(15); // sleep 15 sec

	DEBUG("producer start write\n");

	for(int i = 0; i < MAX; i++)
	{
		tmp.id = i;
		memcpy(shm + (i % shmblocks), &tmp, sizeof(packet));
	}

	DEBUG("producer write finish\n");

	if(munmap(shm, shmblocks * sizeof(packet)) == -1)
	{
		DIE("munmap");
	}

	if(shm_unlink("tmpfile") == -1)
	{
		DIE("shm_unlink");
	}

	return 0;
}