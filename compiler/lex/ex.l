%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 256

int position;
int line;
int tail;
char *hash_table[MAX_BUFFER];
void creat();
int lookup(char*);
int insert(char*);
void dump();
char* cut(char*, int);

%}

num 	[0-9]
ch	[a-zA-Z_$]
numch	[a-zA-Z_0-9_$]
first	[a-zA-Z_$]
symbol ","|":"|";"|"("|")"|"["|"]"|"{"|"}"
operator "+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"!"|"++"|"--"|">="|"<="|"=="|"!="|"&&"|"||"
pstr	["]([^"\n]|"\"\""|"\\\"")*["]
wrong 	["][^\n]*["]
comment [/][*]([^*]|[*]*[^*/])*[*]+[/]

%%

do |
if |
for |
int |
new |
try |
byte |
case |
char |
else |
long |
this |
true |
void |
break |
catch |
class |
false |
final |
float |
short |
while |
double |
public |
return |
static |
string |
switch |
boolean |
default |
extends |
finally |
private |
continue |
protected |
implements		{ printf("Line: %d,1st char: %d, \"%s\" is a \"reserved word\".\n",line,position,yytext); 
			  position+=yyleng; }	
"//".* |
{comment}		{ printf("Line: %d,1st char: %d, \"%s\" is a \"comment\".\n",line,position,yytext); 
			  position+=yyleng; }

{pstr}			{ printf("Line: %d,1st char: %d, %s is a \"string\".\n",line,position,cut(yytext,yyleng));
			  position+=yyleng; }

{wrong}			{ printf("Line: %d,1st char: %d, %s is an error \"string\".\n",line,position,yytext);
			  printf("      ERROR on %s : You may have \' \" \' in your string.\n",yytext);
			  position+=yyleng; }

\n			{ line++; position=1;}

[-]?{num}+		{ printf("Line: %d,1st char: %d, \"%s\" is an \"Interger\".\n",line,position,yytext); 
			  position+=yyleng; }

[-]?{num}+[.]{num}+[eE][-+]?{num}+[.]{num}+ |
[-]?{num}+[.]{num}+[eE][-+]?{num}+ |
[-]?{num}+[eE][-+]?{num}+[.]{num}+ |
[-]?{num}+[eE][-+]?{num}+ |
[-]?{num}+[.]{num}+	{ printf("Line: %d,1st char: %d, \"%s\" is a \"real\".\n",line,position,yytext); 
		  	  position+=yyleng; }  

{symbol} 		{ printf("Line: %d,1st char: %d, \"%s\" is a \"symbol\".\n",line,position,yytext); 
			  position+=yyleng; 
			 }	

{operator} 		{ printf("Line: %d,1st char: %d, \"%s\" is an \"operator\".\n",line,position,yytext); 
			  position+=yyleng; }

{ch}+{numch}*		{ printf("Line: %d,1st char: %d, \"%s\" is an \"ID\".\n",line,position,yytext); 
			  position+=yyleng;
			  int p=lookup(yytext);
			  if(p==-1)
				tail=insert(yytext); 
			}
		
{num}+{numch}*	{ printf("Line : %d,1st char: %d, \"%s\" is an \"ID\".\n",line,position,yytext);
		  printf("      ERROR on \"%s\" : You have invaild ID name.\n",yytext);
		  position+=yyleng; }
 
.		{ position++; }

%%

int main()
{
	position=1;
	line=1;
	tail=-1;
	
	creat();
	yylex();
	dump();
	return 0;
}

void creat()
{
	int i;
	for(i=0;i<MAX_BUFFER;i++)
		hash_table[i]=NULL;
	return ;
}

int lookup(char *s)
{
	int seat=0;
	while( hash_table[seat]!=NULL && strcmp(hash_table[seat],s) )
		seat++;	
	if(hash_table[seat]!=NULL)
		return seat;
	return -1;
}

int insert(char *s)
{
	int seat=tail+1;
	hash_table[seat]=(char*) malloc(sizeof(char)*MAX_BUFFER);
	strcpy( hash_table[seat] , s);
	return seat;
}

void dump()
{
	printf("The symbol table contains : \n");
	int seat=0;
	while(hash_table[seat]!=NULL)
		printf("%s\n",hash_table[seat++]);
	return ;
}

char* cut(char* s, int len)
{
	char* str;
	str=(char*) malloc(sizeof(char)*MAX_BUFFER);
	strcpy(str,s);
	int i=0;
	for( i=0 ; i<len ; i++)
	{	
		if(i<len-1)
		{
			if((str[i]=='"' || str[i]=='\\') && str[i+1]=='"')
			{	
				int j=i;
				for(j=i;j<len-1;j++)
					str[j]=str[j+1];
				str[--len]=0;
			}		
		}
	}
	return str;
}
