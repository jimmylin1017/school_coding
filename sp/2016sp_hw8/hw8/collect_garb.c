/*
 *	collect_garb :
 *	This function has the following responsibilities :
 *		1) Call zap_servlet
 *		2) Remove the head of the pending tray
 *	collect_garb is activated by the garbage_time semaphore
 */

#include "sms.h"

void *collect_garb(void *info) { /* garbage collector */

	Pending *cur_pend = NULL;

	while(TRUE)
	{
		sem_wait(&garbage_time);
		pthread_mutex_lock(&pending_lock);

		// 1) Call zap_servlet
		zap_servlet(pending_stack->head);

		// 2) Remove the head of the pending tray
		cur_pend = pending_stack;
		pending_stack = pending_stack->tail;

		pthread_mutex_unlock(&pending_lock);

		free(cur_pend);
	}

	return NULL;
}
