/*
 *	list_stats produces a report from the stats heap
 */

#include "sms.h"

void list_stats(void) { /* Summmarise statistics */
	
	Stats *cur_state = NULL;

	double connect_time, aborted, size;
	int total_connect;
	connect_time = total_connect = aborted = size = 0;

	pthread_mutex_lock(&history_lock);

	cur_state = history;
	while(cur_state != NULL)
	{
		connect_time += cur_state->connect;
		size += cur_state->size;
		if(cur_state->aborted == TRUE)
			aborted++;
		total_connect++;

		cur_state = cur_state->next;
	}

	pthread_mutex_unlock(&history_lock);

	if(total_connect > 0)
	{
		printf("%d connections\n", total_connect);
	    printf("%.2lf aborted\n", aborted / total_connect);
	    printf("average connect = %.2lf seconds\n", connect_time / total_connect);
	    printf("average size = %.2lf bytes\n", size / total_connect);
	}
	else
		printf("No connections on record\n");
}
