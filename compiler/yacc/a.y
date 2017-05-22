%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 256

extern char *yytext;
extern int yyleng;
extern int yylex();

void yyerror(char*);
void duplicate(char*);

extern int position; /* char 的位置 */
extern int line; /* 當前的行數 */
extern int tail; /* hash table 中的最後一個元素 */
extern int layer; /* 判斷括號的層數 */
extern int newline; /* 判斷是否遇到 end of line */
extern int comment; /* 判斷是否是 comment */
extern int mistake; /* 判斷是否有錯誤 */

extern char* hash_table[MAX_BUFFER]; /* 存放 id */
extern int hash_layer_table[MAX_BUFFER]; /* 對應位置 id 所在層數 */
extern char id_name[MAX_BUFFER]; /* 暫存當下的 id */
extern char  buffer[MAX_BUFFER]; /* 存放要輸出的字串(行) */
extern char  error_msg[MAX_BUFFER]; /* 紀錄錯誤資訊 */
extern char  error_msg2[MAX_BUFFER]; /* 錯誤資訊的 buffer */



/* Function */

extern void creat();
extern int lookup(char* id);
extern int insert(char* id);
extern void dump();
extern void format_str(char* s, int len);
extern void check_layer(char c);
extern void push_in_buffer(int len, char *s);
extern void handle_space(char* s);
extern void print_info();
extern void handle_error();
extern void have_newline();

%}

%token CLASS MAIN THIS 
%token IF ELSE SWITCH CASE DEFAULT FOR DO WHILE CONTINUE BREAK
%token TRY CATCH
%token TRUE FALSE
%token VOID INT FLOAT DOUBEL CHAR BOOLEAN STRING
%token NEW CONST FINAL STATIC
%token PRINT READ 
%token PUBLIC PROTECTED PRIVATE EXTENDS FINALLY
%token IMPLEMENTS RETURN

%token DOUBLE_OPERATOR COMPARE_BOOL CONNECT_BOOL EQUAL
%token REAL_DATA INT_DATA STRING_DATA
%token ID

%start START

%%
class_modifier : PROTECTED | PRIVATE | PUBLIC ;
data_modifier : STATIC | FINAL | CONST ;
data_type : VOID | INT | FLOAT | DOUBEL | CHAR | BOOLEAN | STRING ; 
prefix : DOUBLE_OPERATOR | '+' | '-' ;
postfix : DOUBLE_OPERATOR ;
const_expr : REAL_DATA | INT_DATA | STRING_DATA ;


/**** Java program start point ****/

START :
 | class_declarations START 
 ;  

/**** class_declarations ****
*
* modifier class id { ... }
* class id { ... }
* 包含 extends 和 implements
*
****/

class_declarations : class_modifier CLASS ID '{' statement '}'
 | CLASS ID '{' statement '}'
 | class_modifier CLASS ID class_extends '{' statement '}'
 | CLASS ID class_extends '{' statement '}'
 | class_modifier CLASS ID class_implements class_implements_list '{' statement '}'
 | CLASS ID class_implements class_implements_list '{' statement '}'
 ;
 
class_extends : EXTENDS ID
 ;

class_implements : IMPLEMENTS ID
 ;

class_implements_list : 
 | ',' ID class_implements_list
 ;

/**** variable_declarations ****
*
* modifier type id
* type id
* class_id id = new class_id()
*
****/
 
variable_declarations : data_modifier data_type identifier_declarations ';'
 | data_type identifier_declarations ';'
 | ID identifier_declarations ID '(' ')' ';'
 | error
 ;

/**** include array identifier declaration ****

identifier -> id
identifier -> id = ?
identifier -> id = new ?

array -> id = new type [ ... ]


[] id = new type [ ... ]

****/

identifier_declarations : identifier identifier_list 
 | '[' ']' array array_list
 ;

/**** Simple identifier ****

id
id = ?
id = new ?

****/ 

identifier : ID { duplicate(id_name); } 
 | ID EQUAL expression { duplicate(id_name); }
 | ID EQUAL NEW { duplicate(id_name); }
 ;

identifier_list :
 |',' identifier identifier_list
 ;

/**** array identifier ****
*
* id = new type [ ... ]
*
****/ 

array :ID EQUAL NEW data_type '[' expression ']' { duplicate(id_name); }
 ;

array_list : 
 |',' array array_list
 ;

 
/**** condition ****
*
* if else 條件判斷
*
****/ 

condition : IF '(' boolean_expr boolean_expr_list ')' simple_or_compound
 | IF '(' boolean_expr boolean_expr_list ')' simple_or_compound ELSE simple_or_compound
 ;

simple_or_compound : simple
 | compound
 ; 

boolean_expr : expression COMPARE_BOOL expression
 | TRUE
 | FALSE
 ;
 
boolean_expr_list : 
 | CONNECT_BOOL boolean_expr boolean_expr_list
 ;
 
compound : '{' statement '}' 
 ;

/**** Loop ****
*
* 處理 For 和 While 兩種迴圈
*
* For 需要多兩個判斷 for_init 和 for_update
*
* loop 裡面的 simple, statement, if else 要特別處理 (加入 break, continue)
*
*
****/ 

loop : WHILE '(' boolean_expr boolean_expr_list ')' loop_simple_or_compound
 | DO loop_compound WHILE '(' boolean_expr boolean_expr_list ')' ';'
 | FOR '(' for_init ';' boolean_expr boolean_expr_list ';' for_update ')' loop_simple_or_compound
 ;

loop_condition : IF '(' boolean_expr boolean_expr_list ')' loop_simple_or_compound
 | IF '(' boolean_expr boolean_expr_list ')' loop_simple_or_compound ELSE loop_simple_or_compound
 ; 

loop_simple_or_compound : loop_simple
 | loop_compound
 ;

for_init : INT for_init_assign for_init_assign_list 
 | for_init_assign for_init_assign_list
 ;

for_init_assign : ID EQUAL expression
 ;

for_init_assign_list :
 |',' for_init_assign for_init_assign_list
 ;

for_update : ID postfix
 | prefix ID
 ;

loop_compound : '{' loop_statement '}'
 ;

/**** try catch finally ****
*
* 例外捕捉
*
****/

try_catch_finally : TRY compound CATCH '(' parameter ')' compound FINALLY compound
 | TRY compound CATCH '(' parameter ')' compound
 ;

/**** Switch Case Default ****
*
* Switch Case 有特別的 switch_statement
*
****/

switch_case_default : SWITCH '(' ID ')' switch_compound

switch_compound : '{' switch_statement '}'
 | '{' switch_statement DEFAULT ':' statement '}'
 ;

switch_statement : 
 | CASE const_expr ':' statement BREAK ';' switch_statement
 | CASE const_expr ':' statement switch_statement
 ;
 
 
/**** function parameter ****
*
* function 參數用
* type id 要一起出現
*
****/

parameter : 
 | argv argv_list 
 ;

argv : data_type ID 
 ;

argv_list : 
 |',' argv argv_list 
 ;

/**** statement ****
*
* 變數宣告
*
* { ... } 中可能出現的所有情況
*
****/

statement : 
 | compound statement
 | simple statement
 | condition statement
 | loop statement
 | return statement
 | method_declaration statement
 | variable_declarations statement
 | try_catch_finally statement
 | switch_case_default statement
 ;

loop_statement : 
 | loop_compound loop_statement
 | simple loop_statement
 | loop_condition loop_statement
 | loop loop_statement
 | return loop_statement
 | method_declaration loop_statement
 | variable_declarations loop_statement
 | try_catch_finally loop_statement
 | CONTINUE ';'
 | BREAK ';'
 ;
 
 
/**** method_declaration ****
*
* function 中可能出現的所有情況
*
* method_modifier = class_modifier -> PROTECTED | PRIVATE | PUBLIC
*
****/

method_declaration : class_modifier data_modifier data_type ID '(' parameter ')' '{' statement '}'
 | class_modifier data_type ID '(' parameter ')' '{' statement '}'
 | data_type ID '(' parameter ')' '{' statement '}'
 | MAIN '(' ')' '{' statement '}'
 ;

/****  simple ****
*
* name++ 和 name-- 在 factor 中
*
****/

loop_simple : name EQUAL expression ';'
 | PRINT '(' expression ')' ';'
 | READ '(' name ')' ';'
 | expression ';'
 | CONTINUE
 | BREAK
 ;

simple : name EQUAL expression ';'
 | PRINT '(' expression ')' ';'
 | READ '(' name ')' ';'
 | expression ';'
 ;
 
name : ID
 | ID '.' ID
 ;

expression : term
 | expression '+' term
 | expression '-' term
 ;

term : factor factor_list
 ;

/**** factor ****
*
* 多兩個陣列
*
****/ 

factor : ID
 | ID '[' ID ']'
 | ID '[' INT_DATA ']'
 | const_expr
 | '(' expression ')'
 | prefix name
 | name postfix
 | method_invocation 
 ;

factor_list : 
 | '*' factor
 | '/' factor
 ;
 
method_invocation : name '(' argument ')'
 ;

/**** function call argument ****
*
* 呼叫 function 時要打的參數
*
****/
 
argument : 
 | expression argument_list
 ; 

argument_list : 
 |',' expression argument_list
 ;

return : RETURN expression ';' '\n'
 ;
%%

int main()
{
	creat();
	yyparse();
	return 0;
}

void yyerror(char *str)
{
	mistake = 1;
	sprintf(error_msg2,"> ERROR : Line %d at %d [%s] has %s. \n",line, position-yyleng+1, yytext, str);
	strcat(error_msg, error_msg2);
	return ;
}


/* 判斷重複 id 沒有重複就新增 */
void duplicate(char *s)
{

	if( lookup(s) == -1)
	{
		insert(s);
	}
	else
	{
		mistake = 1;
		sprintf(error_msg,"> ERROR : Line %d ,\'%s\' is a duplicate identifier.\n",line,s);
	}
}
