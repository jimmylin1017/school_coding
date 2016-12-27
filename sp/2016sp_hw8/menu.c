/*
 *	menu :
 *	A generalised menu function
 *	The argument is base of an array of Menu_item, which
 *	must be suitably NULL-teminated
 */

#include "sms.h"

void menu(Menu_item *menu) {

	char input[10];
	int i;

	while(TRUE)
	{
		printf("\n");
		printf("        1)List number of current connections\n\n");
		printf("        2)Summarise statistic\n\n");
		printf("        3)Re-start statistic\n\n");
		printf("        4)Zap stale client and free memory\n\n");
		printf("Please choose (1 - 4) : ");
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';

		for(i = 0; i < 4; i++)
		{
			if(strcmp(input, menu[i].chat) == 0)
				menu[i].act();
		}
	}
}
