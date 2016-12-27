/*
 *	list_conn looks for live connections
 *	It reports the total number and the age of the oldest
 */

#include "sms.h"

void list_conn(void) {	/* list number of current connections */
	
	Servlet *slt = NULL;

	time_t current_time = time(NULL);

	int connect_num = 0;
	int oldest_age = 0;
	int temp_age = 0;

	pthread_mutex_lock(&door_lock);

	slt = door->next;
	while(slt != door)
	{
		temp_age = difftime(current_time, slt->start);
		if(temp_age > oldest_age)
			oldest_age = temp_age;
		connect_num++;
		slt = slt->next;
	}

	pthread_mutex_unlock(&door_lock);

	printf("There are %d live connections\n", connect_num);
	printf("The oldest began %d seconds ago\n", oldest_age);
}
