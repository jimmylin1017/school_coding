/*
 *  timer.c : contains two timing functions to measure process time
 */

#include <unistd.h>
#include <stdio.h>
#include "shell.h"

/* Storage for baseline times. */
static clock_t start_time;

/* Save a baseline of user and system CPU times, plus wallclock time. */
void set_timer(void) {
	struct tms tmbuf;
	/* Fill in code. */
	start_time = times(&tmbuf);
}


/* Get second set of times, and take delta to get wallclock time.  Display. */
void stop_timer(void) {
	struct tms tmbuf;
	clock_t end_time;
	double ticks;

	ticks = sysconf(_SC_CLK_TCK);

	/* Get delta times and print them out.
	 *
	 * Fill in code. */
	end_time = times(&tmbuf);
	printf("real:%.3f user:%.3f system:%.3f\n", (end_time - start_time) / ticks, tmbuf.tms_cutime / ticks, tmbuf.tms_cstime / ticks);
}

