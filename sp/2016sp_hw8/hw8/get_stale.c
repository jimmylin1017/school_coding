/*
 *	get_stale merely locates a stale servlet
 *	It returns a valid pointer on success
 *	It returns NULL if no stale servlets are found
 */

#include "sms.h"

Servlet *get_stale(int secs) { /* find ONE stale client */

	Servlet *slt = NULL;
	time_t now = time(NULL);
	slt = door->next;
	while(slt != door)
	{
		if(difftime(now, slt->start) > secs)
			break;
		slt = slt->next;
	}

	if(slt == door)
		return NULL;
	else
		return slt;
}

