/*
 *	zero_stats just frees the stats stack (means "history")
 */

#include "sms.h"

void zero_stats(void) { /* re-start statistics */
	
	State *cur_state = NULL;
	State *temp = NULL;

	pthread_mutex_lock(&history_lock);

	cur_state = history;
	while(cur_state != NULL)
	{
		temp = cur_state;
		cur_state = cur_state->next;
		free(temp);
	}

	history = NULL

	pthread_mutex_unlock(&history_lock);
}
