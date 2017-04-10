%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

int position;
int line;
int tail;
char* hash_table[MAX_BUFFER];

void creat();
int lookup(char* id);
int insert(char* id);
void dump();
char* format_str(char* s, int len);
void count_line(char* s);

%}

num [0-9]
snum [-+]?{num}+
fnum [-]?{num}+[.]{num}+[eE][-+]?{num}+|[-]?{num}+[eE][-+]?{num}+|[-]?{num}+[.]{num}+
xfnum [-]?{num}+[.]+{num}+|[-]?{num}+[.]+{num}+[eE][-+]?{num}+|[-]?{num}+[.]+|[-]?[.]+{num}+
ch [a-zA-Z_$]
id [a-zA-Z_$]+[a-zA-Z_0-9_$]*
xid [0-9]+[a-zA-Z_0-9_$]*
symbol ","|":"|";"|"("|")"|"["|"]"|"{"|"}"
operator "++"|"--"|"<="|">="|"=="|"!="|"+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"&&"|"||"|"!"
str \"(\\['"bfnrt\\]|[^\\"])*\"
xstr ["].*["]
comment [/][*]([^*]|[*]*[^/])*[*]+[/]
eol \r\n|\n
%%

implements |
protected |
continue |
boolean |
default |
extends |
finally |
private |
double |
public |
return |
static |
string |
switch |
break |
catch |
class |
const |
false |
final |
float |
short |
while |
byte |
case |
char |
else |
long |
this |
true |
void |
for |
int |
new |
try |
do |
if	{
		printf("Line: %d,1st char: %d, \"%s\" is a \"reserved word\".\n", line, position, yytext); 
		position += yyleng;
	}	

"//".* |
{comment}	{
				printf("Line: %d,1st char: %d, \"%s\" is a \"comment\".\n", line, position, yytext);
				count_line(yytext);
				position += yyleng;
			}

{str}+	{
			printf("Line: %d,1st char: %d, %s is a \"string\".\n", line, position, format_str(yytext,yyleng));
			printf("      Original: %s\n", yytext);
	  		position += yyleng;
		}

{xstr}	{
			printf("Line: %d,1st char: %d, %s is an error \"string\".\n", line, position, yytext);
			position += yyleng;
		}

{eol}	{
			/* End of Line */
			line++;
			position = 1;
		}

{snum}	{
			/* minus num */
			printf("Line: %d,1st char: %d, \"%s\" is an \"Interger\".\n", line, position, yytext); 
			position += yyleng;
		}


{fnum}	{
			/* float and science num */
			printf("Line: %d,1st char: %d, \"%s\" is a \"real\".\n", line, position, yytext); 
			position += yyleng;
		}

{xfnum}	{
			/* float and science num */
			printf("Line: %d,1st char: %d, \"%s\" is an error \"real\".\n", line, position, yytext); 
			position += yyleng;
		}

{symbol}	{
				/* Symbol */
				printf("Line: %d,1st char: %d, \"%s\" is a \"symbol\".\n", line, position, yytext); 
				position += yyleng; 
			}	

{operator}	{
				/* Operators */
				printf("Line: %d,1st char: %d, \"%s\" is an \"operator\".\n", line, position, yytext); 
			 	position += yyleng;
			}

{id}		{
				/* IDs */
				printf("Line: %d,1st char: %d, \"%s\" is an \"ID\".\n", line, position, yytext); 
				position += yyleng;
				
				int p = lookup(yytext);
				if( p == -1 )
					tail = insert(yytext); 
			}
		
{xid}	{
			/* Error id format */
			printf("Line: %d,1st char: %d, \"%s\" is an error \"ID\".\n", line, position, yytext);
			//printf("      ERROR on \"%s\" : You have invaild ID name.\n", yytext);
			position += yyleng;
		}
 
.	{
		/* ignore bad characters */
		position++;
	}

%%

int main()
{
	position = 1; /* char position in line */
	line = 1; /* line number counter */
	tail = -1; /* the last index in hash table */
	
	creat(); /* create hash table for id */
	yylex(); /* run lex match program */
	dump(); /* print hash table */
	return 0;
}

void creat()
{
	int i;
	for( i = 0; i<MAX_BUFFER; i++ )
		hash_table[i] = NULL;

	return ;
}

int lookup( char *id )
{
	int index = 0;

	/* find the index of id in hash table */
	while( hash_table[index] != NULL )
	{
		if( !strcmp(hash_table[index], id) )
			return index;
		index++;
	}

	return -1;
}

int insert( char *id )
{
	int index = tail + 1;
	hash_table[index] = (char*)malloc(sizeof(char) * MAX_BUFFER);
	strcpy(hash_table[index], id);
	return index;
}

void dump()
{
	printf("The symbol table contains : \n");
	
	int i = 0;
	for( i = 0; i<=tail; i++ )
		printf("%s\n", hash_table[i]);
		
	return ;
}

/* count new line in comment */

void count_line(char* s)
{
	int i = 0;
	for(i=0; i<strlen(s); i++)
	{
		if(s[i] == '\n')
		{
			line++;
			position = 1;
		}
		else
		{
			position++;
		}
	}
}


/* format_str(yytext,yyleng) */

char* format_str(char* s, int len)
{
	char* fs;
	fs = (char*)malloc(sizeof(char) * MAX_BUFFER);
	strcpy(fs, s);
	
	int i = 0;
	for( i=0; i<len-1; i++)
	{	
		if( fs[i] == '\\' && fs[i+1] == '"' || fs[i] == '\\' && fs[i+1] == '\\' )
		{
			int j = i;
			for( j = i; j<len-1; j++ )
			{
				fs[j] = fs[j+1];
			}
			len--;
			fs[len] = '\0';
		}
	}

	return fs;
}