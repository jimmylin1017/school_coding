/*
Five philosophers are seated around a circular table. Each philosopher has a plate of spaghetti.
The spaghetti is so slippery that a philosopher needs two forks to eat it. Between each pair of plates is one fork.

The life of a philosopher consists of alternate periods of eating and thinking.
When a philosopher gets hungry, she tries to acquire her left and right fork, one at a time, in either order.
If successful in acquiring two forks, she eats for a while, then puts down the forks and continues
to think. The key question is: can you write a program for each philosopher that does what it is
supposed to do and never gets stuck? (It has been pointed out that the two-fork requirement is
somewhat artificial; perhaps we should switch from Italian to Chinese food, substituting rice for
spaghetti and chopsticks for forks.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define N 5 /* number of philosophers */
#define LEFT (i+N-1)%N /* number of i's left neighbor */
#define RIGHT (i+1)%N /* number of i's right neighbor */
#define THINKING 0 /* philosopher is thinking */
#define HUNGRY 1 /* philosopher is trying to get forks */
#define EATING 2 /* philosopher is eating */
#ifdef _DEBUG
	#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

typedef pthread_mutex_t semaphore; /* semaphores are a special kind of int */
int state[N]; /* array to keep track of everyone's state */
semaphore mutex; /* mutual exclusion for critical regions */
semaphore s[N]; /* one semaphore per philosopher */
pthread_t philosopher_thread[N];
int running;

void* philosopher( void* i );
void take_forks( int i );
void put_forks( int i );
void test( int i );
void think( int i );
void eat( int i );
void program_stop();

int main()
{
	int* philosopher_num[N];
	running = TRUE;
	signal( SIGINT, program_stop ); // Ctrl + C
	pthread_mutex_init( &mutex, NULL );

	for( int i = 0 ; i < N ; i++ )
	{
		philosopher_num[i] = malloc( sizeof( int ) );
		*philosopher_num[i] = i;
		pthread_mutex_init( &s[i], NULL );
		pthread_mutex_lock( &s[i] );
		philosopher_thread[i] = i;
		pthread_create( &philosopher_thread[i], NULL, philosopher, (void*) philosopher_num[i] );
	}

	while(TRUE && running)
	{
		pthread_mutex_lock( &mutex );
		printf( "============\n" );
		for( int i = 0 ; i < N ; i++ )
		{
			if( state[i] == THINKING )
				printf("%d : THINKING\n", i);
			else if( state[i] == HUNGRY )
				printf("%d : HUNGRY\n", i);
			else
				printf("%d : EATING\n", i);
		}
		printf( "============\n" );
		pthread_mutex_unlock( &mutex );
		sleep( 1 );
	}

	for( int i = 0 ; i < N ; i++ )
	{
		free( philosopher_num[i] );
		pthread_join( philosopher_thread[i], NULL );
	}

	printf("All philosopher STOP!!\n");

	return 0;
}


void* philosopher( void* i ) /* i: philosopher number, from 0 to N1 */
{
	int _i = *( (int*) i );
	while (TRUE && running)
	{ /* repeat forever */
		DEBUG("In philosopher( %d )\n", _i);
		think(_i); /* philosopher is thinking */
		take_forks(_i); /* acquire two forks or block */
		eat(_i); /* yum-yum, spaghetti */
		put_forks(_i); /* put both forks back on table */
	}

	printf("philosopher %d STOP!\n", _i);

	return NULL;
}

void take_forks( int i ) /* i: philosopher number, from 0 to N1 */
{
	DEBUG("In take_forks( %d )\n", i);
	pthread_mutex_lock( &mutex ); /* enter critical region */
	state[i] = HUNGRY; /* record fact that philosopher i is hungry */
	test(i); /* try to acquire 2 forks */
	pthread_mutex_unlock( &mutex ); /* exit critical region */
	pthread_mutex_lock( &s[i] ); /* block if forks were not acquired */
}

void put_forks( int i ) /* i: philosopher number, from 0 to N1 */
{
	DEBUG("In put_forks( %d )\n", i);
	pthread_mutex_lock( &mutex ); /* enter critical region */
	state[i] = THINKING; /* philosopher has finished eating */
	test(LEFT); /* see if left neighbor can now eat */
	test(RIGHT); /* see if right neighbor can now eat */
	pthread_mutex_unlock( &mutex ); /* exit critical region */
}

void test( int i ) /* i: philosopher number, from 0 to N1 */
{
	DEBUG("In test( %d )\n", i);
	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	{
		DEBUG("%d EATING\n", i);
		state[i] = EATING;
		pthread_mutex_unlock( &s[i] );
	}
}

void think( int i )
{
	DEBUG("In think( %d )\n", i);
	int think_time = rand() % 2 + 1;
	sleep( think_time );
}

void eat( int i )
{
	DEBUG("In eat( %d )\n", i);
	int eat_time = rand() % 3 + 1;

	//printf("%d eating\n",i);

	sleep( eat_time );
}

void program_stop()
{
	running = FALSE;
}