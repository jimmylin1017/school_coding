%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

#define MAX_BUFFER 256

int position = 0; /* char 的位置 */
int line = 1; /* 當前的行數 */
int tail = -1; /* hash table 中的最後一個元素 */
int layer = 0; /* 判斷括號的層數 */
int comment = 0; /* 判斷是否是 comment */
int mistake = 0; /* 判斷是否有錯誤 */

char* hash_table[MAX_BUFFER]; /* 存放 id */
int hash_layer_table[MAX_BUFFER]; /* 對應位置 id 所在層數 */
char id_name[MAX_BUFFER]; /* 暫存當下的 id */
char  buffer[MAX_BUFFER]; /* 存放要輸出的字串(行) */
char  error_msg[MAX_BUFFER]; /* 紀錄錯誤資訊 */
char  error_msg2[MAX_BUFFER]; /* 錯誤資訊的 buffer */


/* Function */

void creat();
int lookup(char* id);
int insert(char* id);
void dump();
void format_str(char* s, int len);
void check_layer(char c);
void push_in_buffer(int len, char *s);
void handle_space(char* s);
void print_info();
void handle_error();
void have_newline();

%}

num [0-9]
ch [a-zA-Z_$]

num_int [-]?{num}+
num_real [-]?{num}+[.]{num}+[eE][-+]?{num}+|[-]?{num}+[eE][-+]?{num}+|[-]?{num}+[.]{num}+
num_real_error [-]?{num}+[.]+{num}+|[-]?{num}+[.]+{num}+[eE][-+]?{num}+|[-]?{num}+[.]+|[-]?[.]+{num}+

id [a-zA-Z_$]+[a-zA-Z_0-9_$]*
id_error [0-9]+[a-zA-Z_0-9_$]*

bracket "("|")"|"["|"]"|"{"|"}"
punctuation ";"|":"|","|"."
equal_operator "="
single_operator "+"|"-"|"*"|"/"|"%"
double_operator "++"|"--"
compare_bool "<="|">="|"=="|"!="|"<"|">"
connect_bool "&&"|"||"

str \"(\\['"bfnrt\\]|[^\\"])*\"
str_error ["].*["]

comment [/][/].*
muti_comment [/][*]([^*]|[*]*[^*/])*[*]+[/]


space [ ]
tab \t
eol \r\n|\n
dot .

%%

{comment}	{ comment = 1; }
{muti_comment}	{ comment = 1; }

class 		{ push_in_buffer(yyleng, yytext); return CLASS; }
this 		{ push_in_buffer(yyleng, yytext); return THIS; }
main		{ push_in_buffer(yyleng, yytext); return MAIN; }

if 			{ push_in_buffer(yyleng, yytext); return IF; }
else		{ push_in_buffer(yyleng, yytext); return ELSE; }
switch 		{ push_in_buffer(yyleng, yytext); return SWITCH; }
case 		{ push_in_buffer(yyleng, yytext); return CASE; }
default 	{ push_in_buffer(yyleng, yytext); return DEFAULT; }
for 		{ push_in_buffer(yyleng, yytext); return FOR; }
while 		{ push_in_buffer(yyleng, yytext); return WHILE; }
do 			{ push_in_buffer(yyleng, yytext); return DO; }
continue	{ push_in_buffer(yyleng, yytext); return CONTINUE; }
break		{ push_in_buffer(yyleng, yytext); return BREAK; }

try 		{ push_in_buffer(yyleng, yytext); return TRY; }
catch		{ push_in_buffer(yyleng, yytext); return CATCH; }

true 		{ push_in_buffer(yyleng, yytext); return TRUE; }
false 		{ push_in_buffer(yyleng, yytext); return FALSE; }

void		{ push_in_buffer(yyleng, yytext); return VOID; }
int 		{ push_in_buffer(yyleng, yytext); return INT; }
float 		{ push_in_buffer(yyleng, yytext); return FLOAT; }
boolean		{ push_in_buffer(yyleng, yytext); return BOOLEAN; }
char 		{ push_in_buffer(yyleng, yytext); return CHAR; }
String 		{ push_in_buffer(yyleng, yytext); return STRING; }

new 		{ push_in_buffer(yyleng, yytext); return NEW; }
final 		{ push_in_buffer(yyleng, yytext); return FINAL; }
static 		{ push_in_buffer(yyleng, yytext); return STATIC; }
const		{ push_in_buffer(yyleng, yytext); return CONST; }

print 		{ push_in_buffer(yyleng, yytext); return PRINT; }
read		{ push_in_buffer(yyleng, yytext); return READ; }

extends		{ push_in_buffer(yyleng, yytext); return EXTENDS; }
finally 	{ push_in_buffer(yyleng, yytext); return FINALLY; }
public 		{ push_in_buffer(yyleng, yytext); return PUBLIC; }
private 	{ push_in_buffer(yyleng, yytext); return PRIVATE; }
protected 	{ push_in_buffer(yyleng, yytext); return PROTECTED; }

return 		{ push_in_buffer(yyleng, yytext); return RETURN; }
implements	{ push_in_buffer(yyleng, yytext); return IMPLEMENTS; }
Exception	{ push_in_buffer(yyleng, yytext); return EXCEPTION; }

{bracket}	{ push_in_buffer(yyleng, yytext); check_layer(yytext[0]); return yytext[0]; }
{punctuation}		{ push_in_buffer(yyleng, yytext); return yytext[0]; }
{equal_operator}	{ push_in_buffer(yyleng, yytext); return EQUAL; }	
{single_operator}	{ push_in_buffer(yyleng, yytext); return yytext[0]; }
{double_operator}	{ push_in_buffer(yyleng, yytext); return DOUBLE_OPERATOR; }	
{compare_bool}		{ push_in_buffer(yyleng, yytext); return COMPARE_BOOL; }
{connect_bool}		{ push_in_buffer(yyleng, yytext); return CONNECT_BOOL; }

{str}		{ /*format_str(yytext,yyleng);*/ push_in_buffer(yyleng, yytext); return STRING_DATA; }

{eol}		{ print_info(); have_newline(); }
{space}		{ handle_space(yytext); }
{tab}		{ handle_space(yytext); }

{num_int} 	{ push_in_buffer(yyleng, yytext); return INT_DATA; }
{num_real}	{ push_in_buffer(yyleng, ""); return REAL_DATA; }
{num_real_error}	{ push_in_buffer(yyleng, yytext); handle_error("real number error"); }
{id}		{ push_in_buffer(yyleng, yytext); strcpy(id_name, yytext); return ID; }

{str_error}	{ push_in_buffer(yyleng, yytext); handle_error("string error"); }
{dot}		{ strcat(buffer,yytext); }

%%

int yywrap()
{
	return 1;
}

void creat()
{
	int i;
	tail=-1;
	for(i=0;i<MAX_BUFFER;i++)
	{
		hash_table[i]=NULL;
		hash_layer_table[i]=0;
	}
	return ;
}

int lookup( char *id )
{
	int index = 0;
	
	/* 尋找 id 在 hash table 中的位置 */
	while( hash_table[index] != NULL )
	{
		/* 順便判斷所在的 layer 有無衝突 */
		if( !strcmp(hash_table[index], id) 
			&& hash_layer_table[index] <= layer
			&& hash_layer_table[index] > -1 )
		{
			return index;
		}

		index++;
	}

	return -1;
}

/* 將 id 插入 hash table */
int insert( char *id )
{
	tail = tail + 1;
	hash_table[tail] = (char*)malloc(sizeof(char) * MAX_BUFFER);
	strcpy(hash_table[tail], id);
	hash_layer_table[tail] = layer;
	return 1;
}

/* 印出 hash table 裡面的所有 id */
void dump()
{
	printf("The symbol table contains : \n");
	
	int i = 0;
	for( i = 0; i<=tail; i++ )
		printf("%s\n", hash_table[i]);
		
	return ;
}

/* 把字串中的 \\ -> \ 或 \" -> " */
void format_str( char* s, int len )
{
	char* fs;
	fs = (char*)malloc(sizeof(char) * MAX_BUFFER);
	strcpy(fs, s);
	
	int i = 0;
	for( i=0; i<len-1; i++)
	{	
		if( (fs[i] == '\\' && fs[i+1] == '\"') || (fs[i] == '\\' && fs[i+1] == '\\') )
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
	
	strcat(buffer, fs);

	return ;
}

/* 判斷當下是第幾層 */
void check_layer( char c )
{
	if( c == '(' || c == '{' )
	{
		layer++;
	}
	else if( c == ')' || c == '}' ) 
	{
		layer--;
		
		/* 把除了目前層數的 id 之外的 id 從 hash table 刪掉 */
		int index = 0;
		while( hash_table[index] != NULL )
		{	
			if( hash_layer_table[index] > layer )
			{
				hash_layer_table[index] = -1;
			}
			index++;
		}
	}
	
	return ;
}

/* 將程式碼放入 buffer 中 */
void push_in_buffer( int len, char *s )
{
	position = position + len;
	strcat(buffer, s);
}

/* 處理空白和 Tab */
void handle_space( char* s )
{
	strcat(buffer, s);
}

void handle_error( char* s )
{
	sprintf(error_msg2, "> ERROR : Line %d, Char %d has %s\n", line, position, s);
	strcat(error_msg, error_msg2);
	return ;
}

/* 處理遇到 End of Line */
void have_newline()
{
	position = 0;
	line++;
	/* 清空 buffer */
	int i;
	for(i=0; i<MAX_BUFFER; i++)
	{
		buffer[i] = '\0';
	}
	sprintf(buffer, "Line: %d: ", line);
}

/* 輸出第幾行和錯誤訊息 */
void print_info()
{
	printf("%s\n",buffer);
	if( mistake == 1 )
	{
		printf("%s\n",error_msg);
		/* 清空 error_msg */
		int i;
		for(i=0; i<MAX_BUFFER; i++)
		{
			error_msg[i] = '\0';
		}
		mistake = 0;
	}
}