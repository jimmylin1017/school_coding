/*
 * lookup9 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Internet UDP Sockets
 * The name of the server is passed as resource. PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd, siz;
	static struct sockaddr_in server;
	struct hostent *host;
	static int first_time = 1;

	if (first_time) {  /* Set up server address & create local UDP socket */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

		/* Allocate a socket.
		 * Fill in code. */
		if((host = gethostbyname(resource)) == -1)
		{
			DIE("gethostbyname");
		}

		memset((char *)&server, '\0', sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT); //convert values between host and network byte order
		memcpy((char *)&server.sin_addr, host->h_addr_list[0], host->h_length);
	}

	/* Send a datagram & await reply
	 * Fill in code. */
	siz = sizeof(server);
	sendto(sockfd, sought, sizeof(Dictrec), 0, (struct sockaddr *)&server, siz);
	recvfrom(sockfd, sought, sizeof(Dictrec), 0, (struct sockaddr *)&server, (socklen_t *)&siz);

	if (strcmp(sought->text,"XXXX") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
