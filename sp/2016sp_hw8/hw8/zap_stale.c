/*
 *	zap_stale does the following
 *	for each stale client found
 *		1) Set abort flag
 *		2) Kill the thread
 *		3) Call disconnect
 */

#include "sms.h"

void zap_stale(void) {	/* call disconnect when needed */
	
	Servlet *slt = NULL;

	int stale = 0;
	char *stale_msg = "sorry time's up\n";

	printf("How many seconds counts as stale ? ");
	scanf("%d%*c", &stale );

	/*
		1) Set abort flag
		2) Kill the thread
		3) Call disconnect
	*/
	slt = get_stale(stale);
	if(slt != NULL)
	{
		printf("Found a stale one\n");
		slt->aborted = TRUE;
		write(slt->fd, stale_msg, sizeof(stale_msg));
		pthread_cancel(slt->thread);
		disconnect(slt);
	}
	else
	{
		printf("Not found any stale connection\n");
	}
}
