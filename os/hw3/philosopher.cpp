#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

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

void* philosopher( void* i );
void program_stop( int s );

int running;

class Philosopher_Monitor
{
private:

	int state[N]; /* array to keep track of everyone's state */
	semaphore mutex; /* mutual exclusion for critical regions */
	pthread_cond_t s[N]; /* one semaphore per philosopher */

public:

	Philosopher_Monitor()
	{
		pthread_mutex_init( &mutex, NULL );

		for( int i = 0 ; i < N ; i++ )
		{
			pthread_cond_init( &s[i], NULL );
		}
	}

	void take_forks( int i ) /* i: philosopher number, from 0 to N1 */
	{
		DEBUG("In take_forks( %d )\n", i);
		pthread_mutex_lock( &mutex ); /* enter critical region */
		state[i] = HUNGRY; /* record fact that philosopher i is hungry */
		test(i); /* try to acquire 2 forks */
		pthread_mutex_unlock( &mutex ); /* exit critical region */
	}

	void put_forks( int i ) /* i: philosopher number, from 0 to N1 */
	{
		DEBUG("In put_forks( %d )\n", i);
		pthread_mutex_lock( &mutex ); /* enter critical region */
		state[i] = THINKING; /* philosopher has finished eating */
		pthread_cond_signal( &s[LEFT] );
		pthread_cond_signal( &s[RIGHT] );
		//test(LEFT); /* see if left neighbor can now eat */
		//test(RIGHT); /* see if right neighbor can now eat */
		pthread_mutex_unlock( &mutex ); /* exit critical region */
	}

	void test( int i ) /* i: philosopher number, from 0 to N1 */
	{
		DEBUG("In test( %d )\n", i);
		while(TRUE && running)
		{
			if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
			{
				DEBUG("%d EATING\n", i);
				state[i] = EATING;
				break;
			}
			else
			{
				DEBUG("%d WAITING...\n", i);
				pthread_cond_wait( &s[i], &mutex );
			}
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

	void print()
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
	}

};

Philosopher_Monitor p_monitor;

int main()
{
	pthread_t philosopher_thread[N];
	int* philosopher_num[N];

	running = TRUE;
	signal( SIGINT, program_stop ); // Ctrl + C

	for( int i = 0 ; i < N ; i++ )
	{
		philosopher_num[i] = ( int* )malloc( sizeof( int ) );
		*philosopher_num[i] = i;
		philosopher_thread[i] = i;
		pthread_create( &philosopher_thread[i], NULL, philosopher, (void*) philosopher_num[i] );
	}

	while(TRUE && running)
	{
		p_monitor.print();
		sleep(1);
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
		p_monitor.think(_i); /* philosopher is thinking */
		p_monitor.take_forks(_i); /* acquire two forks or block */
		p_monitor.eat(_i); /* yum-yum, spaghetti */
		p_monitor.put_forks(_i); /* put both forks back on table */
	}

	printf("philosopher %d STOP!\n", _i);

	return NULL;
}

void program_stop( int s )
{
	running = FALSE;
}