/*
 *	listen_port :
 *	The body of the thread which listens on a particular
 *	port number (it's sole argument).
 *	Whenever a new connection is requested it calls
 *	make_servelet_list and then fires off a new thread running.
 *	It must set two fields in the Servlet structure :
 *		1) fd
 *		2) start
 */

#include "sms.h"

Servlet *newnode = NULL;

void make_servelet_list();

void *listen_port(void *info) { /* body of port listener */
	
	struct sockaddr_in server, client;
	int server_fd, client_fd;
	int client_size = sizeof(client);

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		DIE("socket");
	}
	memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT); //convert values between host and network byte order
	server.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY 0.0.0.0 can be any address when have many MAC
	
	int optval = TRUE;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, (socklen_t)sizeof(optval));

	if(bind(server_fd, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		DIE("bind");
	}

	if (listen(server_fd, 128) == -1)
	{
		DIE("listen");
	}

	while ( TRUE )
	{
		if((client_fd = accept(server_fd, (struct sockaddr*)&client, &client_size)) == -1)
		{
			DIE("accept");
		}

		newnode = (Servlet*)malloc(sizeof(Servlet));
		memset(newnode, 0, sizeof(newnode));
		newnode->fd = client_fd;
		newnode->start = time(NULL);
		newnode->aborted = FALSE;
		make_servelet_list();
		pthread_create(&newnode->thread, &attr, &serve_client, (void *)newnode);
	}

	return NULL;
}

void make_servelet_list() {

	pthread_mutex_lock(&door_lock);

	if(door == NULL)
	{
		door = (Servlet*)malloc(sizeof(Servlet));
		door->prev = door;
		door->next = door;
	}

	door->prev->next = newnode;
	newnode->next = door;
	newnode->prev = door->prev;
	door->prev = newnode;
	
	pthread_mutex_unlock(&door_lock);
}
