/*
 * lookup3 : This file does no looking up locally, but instead asks
 * a server for the answer. Communication is by named pipes.
 * The server sits listening on a "well-known" named pipe
 * (this is what is passed to lookup3 as resource)
 * The Client sets up a FIFO for reply, and bundles the FIFO
 * name with the word to be looked up. (See Client in dict.h)
 * Care must be taken to avoid deadly embrace (client & server
 * both waiting for something which can never happen)
 */

#include "dict.h"

static Client me;

void cleanup(int signum) {
	/* Delete named pipe from system. 
	 *
	 * Fill in code. */
	DEBUG("cleanup handler : remove %s\n", me.id);
	unlink(me.id);
	exit(1);
}

int lookup(Dictrec * sought, const char * resource) {
	static int write_fd;
	int read_fd;
	static int first_time = 1;

	if (first_time) {
		first_time = 0;

		DEBUG("first time!\n");

		/* Open existing named pipe for client->server communication.
		 *
		 * Fill in code. */
		write_fd = open(resource, O_WRONLY);

		/* Create temporary named pipe for server->client communication. */
		umask(0);
		tmpnam(me.id);
		/* Fill in code. */
		mkfifo(me.id, 0777);

		/* Register cleanup handler.
		 *
		 * Fill in code. */
		signal(SIGINT, cleanup);
	}

	/* Send server the word to be found ; await reply */
	strcpy(me.word, sought->word);
	/* Fill in code. */
	write(write_fd, me.id, IDSIZE);
    write(write_fd, me.word, WORD);
 

	/* Open the temporary named pipe to get the answer from it.
	 *
	 * Fill in code. */
    read_fd = open(me.id, O_RDONLY);

	/* Get the answer.
	 *
	 * Fill in code. */
    read(read_fd, sought->text, TEXT);

	/* Close the temporary named pipe as done.
	 *
	 * Fill in code. */
    close(read_fd);

	/* If word returned is not XXXX it was found. */
	if (strcmp(sought->text,"XXXX") != 0)
		return FOUND;

	return NOTFOUND;
}
