/*
 *	zap_servlet does the following :
 *		1) Append the message to an appropriate file
 *		2) Capture statistics and push onto stat stack
 *		3) Dispose of the Servlet
 */

#include "sms.h"

void zap_servlet(Servlet *victim) { /* remove and free memeory */
	
	if(victim->aborted == FALSE)
	{
		// 1) Append the message to an appropriate file
		int file_fd = open(victim->dest, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if(file_fd == -1)
		{
			DIE("open");
		}

		write(file_fd, victim->message, sizeof(victim->message));
		close(file_fd);
	}

	// 2) Capture statistics and push onto stat stack
	Stats *newnode = NULL;

	newnode = (Stats*)malloc(sizeof(Stats));
	newnode->cust_ip = victim->cust_ip;		/* IP addr of client */
	strcpy(newnode->dest, victim->dest);	/* addressee */
	newnode->size = victim->chars_read;		/* message size */
	newnode->connect = difftime(victim->finish, victim->start);	/* connect time in secs */
	newnode->aborted = victim->aborted;		/* boolean flag */
	newnode->next = NULL;

	pthread_mutex_lock(&history_lock);

	if(history != NULL)
	{
		newnode->next = history;
	}
	history = newnode;

	pthread_mutex_unlock(&history_lock);

	// 3) Dispose of the Servlet
	pthread_cancel(victim->thread);
	free(victim);
}
