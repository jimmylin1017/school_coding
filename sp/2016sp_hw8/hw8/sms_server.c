/*
 *	sms_server.c :
 *	1. All global variables are defined in sms.h
 *	2. main, which does the following
 *		a) Initialize the circular list
 *		b) Fire off threads for collect_garb and listen_port
 *		c) Run the menu
 */

#include "sms.h"

Servlet *door;			/* entrance to doubly linked list		*/
Pending *pending_stack;	/* pile of stale servlets				*/
Stats * history;		/* start of stats linked list			*/
sem_t garbage_time;		/* schedule garbage collection			*/
pthread_attr_t attr;	/* set to make ALL threads detached		*/

pthread_mutex_t door_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pending_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t history_lock = PTHREAD_MUTEX_INITIALIZER;

void main(int argc, char **argv) {
	
	pthread_t listen_thread;
	pthread_t garbage_thread;

	Menu_item server_menu[] = {
		{"1", list_conn}, {"2", list_stats}, {"3", zero_stats}, {"4", zap_stale}, {NULL, NULL}
	};

	// a) Initialize the circular list
	door = (Servlet*)malloc(sizeof(Servlet));
	door->prev = door;
	door->next = door;
	pending_stack = NULL;
	history = NULL;

	// b) Fire off threads for collect_garb and listen_port
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&listen_thread, &attr, &listen_port, NULL);
	pthread_create(&listen_thread, &attr, &garbage_thread, NULL);

	// c) Run the menu
	menu(server_menu);

	return 0;
}