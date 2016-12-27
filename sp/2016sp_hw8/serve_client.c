/*
 *	serve_client :
 *	The body of the thread of which one is started for each client.
 *	It receives as its argument a pointer to Servlet of which  precisely
 *	two fields : the start time and socket descriptor are non-null.
 *	The main duty of this thread is to conduct a dialog with the client.
 *	Correct termination is the string "---" in a line by itself.
 *	Incorrect termination and over verbose clients must the suitably handled.
 */

#include "sms.h"

void *serve_client(void *info) { /* body of servlet thread */
	
	Servlet *client_info = NULL;
	char server_to_client_msg[SHORTMESS];
	char message[SHORTMESS];
	char dest[MAXDEST];

	client_info = (Servlet*)info;

	memset(server_to_client_msg, 0, sizeof(server_to_client_msg));
	strcpy(server_to_client_msg, "Destination : ");
	write(client_info->fd, server_to_client_msg, sizeof(server_to_client_msg));

	memset(dest, 0, sizeof(dest));
	memset(client_info->dest, 0, sizeof(client_info->dest));
	read(client_info->fd, dest, sizeof(dest));
	strcpy(client_info->dest, dest);

	memset(server_to_client_msg, 0, sizeof(server_to_client_msg));
	strcpy(server_to_client_msg, "Now write your message : finish with ---\n");
	write(client_info->fd, server_to_client_msg, sizeof(server_to_client_msg));

	while(TRUE)
	{
		memset(server_to_client_msg, 0, sizeof(server_to_client_msg));
		strcpy(server_to_client_msg, "--->");
		write(client_info->fd, server_to_client_msg, sizeof(server_to_client_msg));

		memset(message, 0, sizeof(message));
		memset(client_info->message, 0, sizeof(client_info->message));
		read(client_info->fd, message, sizeof(message));
		message[strlen(message) - 2] = '\0';

		//printf("Read Message: %s", message);

		if(strcmp(message, "---") == 0)
		{
			memset(server_to_client_msg, 0, sizeof(server_to_client_msg));
			strcpy(server_to_client_msg, "Bye Bye!\n");
			write(client_info->fd, server_to_client_msg, sizeof(server_to_client_msg));
			break;
		}

		if((strlen(client_info->message) + strlen(message)) + 1 < SHORTMESS)
		{
			strncat(client_info->message, message, (int)strlen(client_info->message));
			strncat(client_info->message, "\n", (int)strlen(client_info->message));
			client_info->chars_read += strlen(client_info->message) + 1;
		}
		else
		{
			printf("Warning: client_info->message full\n");
		}
	}

	disconnect(client_info);

	return NULL;
}
