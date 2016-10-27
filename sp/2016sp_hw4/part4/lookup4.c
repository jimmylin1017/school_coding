/*
 * lookup4 : This file does no looking up locally, but instead asks
 * a server for the answer. Communication is by message queues.
 * The protocol is : messages of type 1 are meant for the server.
 * The client only reads messages whose type matches their own pid.
 * The message queue key is what is passed as resource.
 */
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static ClientMessage snd;
	ServerMessage rcv;
	static int qid;
	static int pid;
	static int first_time = 1;

	if (first_time) { /* open message queue */
		first_time = 0;

		/* Prepare our ClientMessage structure. */
		pid = getpid();
		sprintf(snd.content.id,"%d",pid);
		snd.type = 1L;

		/* Open the message queue.  Use resource pointer value as key.
		 *
		 * Fill in code. */
		key_t key = strtol(resource, NULL, 16);
		qid = msgget(key, 0);
		if(qid == -1)
		{
			perror("msgget");
			exit(1);
		}
	}

	/* Send server the word to be found ; await reply
	 *
	 * Fill in code. */
	strcpy(snd.content.word, sought->word);
	msgsnd(qid, &snd, sizeof(snd.content), 0);
	msgrcv(qid, &rcv, sizeof(rcv.text), pid, 0);




	strcpy(sought->text, rcv.text);

	/* Server returns XXXX when it cannot find request. */
	if (strcmp(rcv.text,"XXXX") != 0)
		return FOUND;

	return NOTFOUND;
}



/*
NAME
       msgrcv, msgsnd - System V message queue operations

SYNOPSIS
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>

       int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);

DESCRIPTION
       The  msgsnd() and msgrcv() system calls are used, respectively, to send
       messages to, and receive messages from, a System V message queue.   The
       calling  process  must  have  write  permission on the message queue in
       order to send a message, and read permission to receive a message.

       The msgp argument is a pointer to a  caller-defined  structure  of  the
       following general form:

           struct msgbuf {
               long mtype;       // message type, must be > 0
               char mtext[1];    // message data
           };

       The  mtext  field is an array (or other structure) whose size is speci‐
       fied by msgsz, a nonnegative integer value.  Messages  of  zero  length
       (i.e.,  no  mtext  field)  are  permitted.  The mtype field must have a
       strictly positive integer value.  This value can be used by the receiv‐
       ing  process  for  message  selection  (see the description of msgrcv()
       below).


       * If msgtyp is 0, then the first message in the queue is read.

       * If  msgtyp  is greater than 0, then the first message in the queue of
         type msgtyp is read, unless MSG_EXCEPT was specified  in  msgflg,  in
         which case the first message in the queue of type not equal to msgtyp
         will be read.

       * If msgtyp is less than 0, then the first message in  the  queue  with
         the  lowest  type  less than or equal to the absolute value of msgtyp
         will be read.

*/