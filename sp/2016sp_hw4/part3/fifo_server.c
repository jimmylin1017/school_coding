/*
 * fifo_server : listen on a named pipe; do lookup ; reply
 *               down another named pipe, the name of which
 *               will be sent by the client (in cli.id)
 *               argv[1] is the name of the local fil
 *               argv[2] is the name of the "well-known" FIFO
 */

#include "dict.h"

int main(int argc, char **argv) {
	struct stat stbuff;
	int read_fd,write_fd;
	Client cli;
	Dictrec tryit;

	if (argc != 3) {
		fprintf(stderr,"Usage : %s <dictionary source> ""<resource / FIFO>\n",argv[0]);
		exit(errno);
	}

	/* Check for existence of dictionary and FIFO (both must exist)
	 *
	 * Fill in code. */
	if(access(argv[1], F_OK) == -1)
    {
    	printf("dictionary source not found!\n");
    	exit(errno);
    }

    if(access(argv[2], F_OK) == -1)
    {
    	printf("resource / FIFO not found!\n");
    	exit(errno);
    }

	/* Open FIFO for reading (blocks until a client connects)
	 *
	 * Fill in code. */
    read_fd = open(argv[2], O_RDONLY);

    if(read_fd == -1)
    {
    	perror("open");
    	exit(1);
    }

	/* Sit in a loop. lookup word sent and send reply down the given FIFO */
	for (;;) {

		/* Read request.
		 *
		 * Fill in code. */
		read(read_fd, cli.id, IDSIZE);
		read(read_fd, cli.word, WORD);
		strcpy(tryit.word, cli.word);

		DEBUG("%s : %s\n",cli.id, tryit.word);
		
		/* Get name of reply fifo and attempt to open it.
		 *
		 * Fill in code. */
		write_fd = open(cli.id, O_WRONLY);
		if(write_fd != -1)
		{
			/* lookup the word , handling the different cases appropriately
			 *
			 * Fill in code. */
			switch(lookup(&tryit, argv[1])) {
				case FOUND:
					/* Fill in code. */
					write(write_fd, tryit.text, TEXT);
					break;
				case NOTFOUND:
					/* Fill in code. */
					write(write_fd, "XXXX", TEXT);
					break;
				case UNAVAIL:
					/* Fill in code. */
					DIE(argv[1]);
			}
			close(write_fd);
		}

		/* close connection to this client (server is stateless)
		 *
		 * Fill in code. */
		
		if(access(cli.id, F_OK) == -1)
		{
			close(read_fd);
			read_fd = open(argv[2], O_RDONLY);
		}
	}
}
