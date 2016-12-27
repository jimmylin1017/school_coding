/*
 *	disconnect is passed a pointer to a Servlet
 *	It should perform the following :
 *		1) Take the servlet out of the circular list
 *		2) Close the socket connection
 *		3) Create a Pending item and push pending stack
 *		4) Alert the garbage collector
 */

#include "sms.h"

void disconnect(Servlet *done) {

	pthread_mutex_lock(&door_lock);

	// 1) Take the servlet out of the circular list
	done->finish = time(NULL);
	done->prev->next = done->next;
	done->next->prev = done->prev;

	// 2) Close the socket connection
	close(done->fd);

	pthread_mutex_unlock(&door_lock);

	// 3) Create a Pending item and push pending stack
	Pending *newnode;

	newnode = (Pending *)malloc(sizeof(Pending));
	newnode->head = done;
	newnode->tail = NULL;

	pthread_mutex_lock(&pending_lock);

	if(pending_stack != NULL)
		newnode->tail = pending_stack;
	
	pending_stack = newnode;

	pthread_mutex_unlock(&pending_lock);

	// 4) Alert the garbage collector
	sem_post(&garbage_time);
}
