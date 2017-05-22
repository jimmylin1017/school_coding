/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "B033040006.y" /* yacc.c:339  */

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


#line 111 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    MAIN = 259,
    THIS = 260,
    IF = 261,
    ELSE = 262,
    SWITCH = 263,
    CASE = 264,
    DEFAULT = 265,
    FOR = 266,
    DO = 267,
    WHILE = 268,
    CONTINUE = 269,
    BREAK = 270,
    TRY = 271,
    CATCH = 272,
    TRUE = 273,
    FALSE = 274,
    VOID = 275,
    INT = 276,
    FLOAT = 277,
    DOUBEL = 278,
    CHAR = 279,
    BOOLEAN = 280,
    STRING = 281,
    NEW = 282,
    CONST = 283,
    FINAL = 284,
    STATIC = 285,
    PRINT = 286,
    READ = 287,
    PUBLIC = 288,
    PROTECTED = 289,
    PRIVATE = 290,
    EXTENDS = 291,
    FINALLY = 292,
    IMPLEMENTS = 293,
    RETURN = 294,
    EXCEPTION = 295,
    DOUBLE_OPERATOR = 296,
    COMPARE_BOOL = 297,
    CONNECT_BOOL = 298,
    EQUAL = 299,
    REAL_DATA = 300,
    INT_DATA = 301,
    STRING_DATA = 302,
    ID = 303
  };
#endif
/* Tokens.  */
#define CLASS 258
#define MAIN 259
#define THIS 260
#define IF 261
#define ELSE 262
#define SWITCH 263
#define CASE 264
#define DEFAULT 265
#define FOR 266
#define DO 267
#define WHILE 268
#define CONTINUE 269
#define BREAK 270
#define TRY 271
#define CATCH 272
#define TRUE 273
#define FALSE 274
#define VOID 275
#define INT 276
#define FLOAT 277
#define DOUBEL 278
#define CHAR 279
#define BOOLEAN 280
#define STRING 281
#define NEW 282
#define CONST 283
#define FINAL 284
#define STATIC 285
#define PRINT 286
#define READ 287
#define PUBLIC 288
#define PROTECTED 289
#define PRIVATE 290
#define EXTENDS 291
#define FINALLY 292
#define IMPLEMENTS 293
#define RETURN 294
#define EXCEPTION 295
#define DOUBLE_OPERATOR 296
#define COMPARE_BOOL 297
#define CONNECT_BOOL 298
#define EQUAL 299
#define REAL_DATA 300
#define INT_DATA 301
#define STRING_DATA 302
#define ID 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 258 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   601

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  358

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      63,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,    56,    61,    49,    53,    50,    60,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    63,    63,    64,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    66,    66,    67,
      68,    68,    68,    73,    74,    85,    86,    87,    88,    89,
      90,    93,    96,    99,   100,   111,   112,   113,   114,   130,
     131,   142,   143,   144,   147,   148,   157,   160,   161,   171,
     172,   175,   176,   179,   180,   181,   184,   185,   188,   202,
     203,   204,   207,   208,   211,   212,   215,   216,   219,   222,
     223,   226,   227,   230,   239,   240,   249,   251,   252,   255,
     256,   257,   268,   269,   272,   275,   276,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   321,   322,
     323,   324,   333,   334,   335,   336,   337,   338,   341,   342,
     343,   344,   347,   348,   349,   352,   353,   354,   357,   366,
     367,   368,   369,   370,   371,   372,   373,   376,   377,   378,
     381,   390,   391,   394,   395,   398
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "MAIN", "THIS", "IF", "ELSE",
  "SWITCH", "CASE", "DEFAULT", "FOR", "DO", "WHILE", "CONTINUE", "BREAK",
  "TRY", "CATCH", "TRUE", "FALSE", "VOID", "INT", "FLOAT", "DOUBEL",
  "CHAR", "BOOLEAN", "STRING", "NEW", "CONST", "FINAL", "STATIC", "PRINT",
  "READ", "PUBLIC", "PROTECTED", "PRIVATE", "EXTENDS", "FINALLY",
  "IMPLEMENTS", "RETURN", "EXCEPTION", "DOUBLE_OPERATOR", "COMPARE_BOOL",
  "CONNECT_BOOL", "EQUAL", "REAL_DATA", "INT_DATA", "STRING_DATA", "ID",
  "'+'", "'-'", "'{'", "'}'", "','", "';'", "'('", "')'", "'['", "']'",
  "':'", "'.'", "'*'", "'/'", "'\\n'", "$accept", "class_modifier",
  "data_modifier", "data_type", "prefix", "postfix", "const_expr", "START",
  "class_declarations", "class_extends", "class_implements",
  "class_implements_list", "variable_declarations",
  "identifier_declarations", "identifier", "identifier_list", "array",
  "array_list", "condition", "simple_or_compound", "boolean_expr",
  "boolean_expr_list", "compound", "loop", "loop_condition",
  "loop_simple_or_compound", "for_init", "for_init_assign",
  "for_init_assign_list", "for_update", "loop_compound",
  "try_catch_finally", "switch_case_default", "switch_compound",
  "switch_statement", "parameter", "argv", "argv_list", "statement",
  "loop_statement", "method_declaration", "loop_simple", "simple", "name",
  "expression", "term", "factor", "factor_list", "method_invocation",
  "argument", "argument_list", "return", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,    43,
      45,   123,   125,    44,    59,    40,    41,    91,    93,    58,
      46,    42,    47,    10
};
# endif

#define YYPACT_NINF -321

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-321)))

#define YYTABLE_NINF -123

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     189,   -29,  -321,  -321,  -321,    32,    37,   189,   -21,    20,
    -321,  -321,    67,    77,   422,    68,    36,    71,  -321,  -321,
    -321,    73,    79,   105,   121,   133,   112,   164,   174,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   185,
     208,   473,  -321,  -321,  -321,  -321,  -321,   173,  -321,  -321,
     422,   473,   516,   538,   101,    26,  -321,   318,   318,   318,
     318,   318,   318,   215,   318,   318,    42,    38,  -321,    81,
    -321,   318,   422,   224,   227,   422,   231,    36,   229,   240,
       6,   242,   509,   370,   282,     6,   293,   473,    26,   232,
      55,   225,   267,   -14,   266,   269,   265,   268,   -11,   538,
     273,   108,   -15,   274,   271,   275,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,   473,   473,  -321,
     473,   473,  -321,   473,   473,  -321,  -321,   285,    36,   422,
     302,   422,   294,   304,  -321,  -321,  -321,   319,   216,   321,
     334,   331,   326,   335,   332,   343,   352,   370,   370,   370,
     370,   370,   337,   370,   370,   370,   353,   319,   357,   147,
     351,   235,   350,   455,   356,   366,   381,  -321,   376,   384,
    -321,  -321,  -321,   388,   382,   385,   538,  -321,   244,   256,
     408,  -321,  -321,  -321,  -321,  -321,  -321,   389,  -321,   413,
     422,   422,     6,   410,   473,   428,   473,   335,     6,   331,
    -321,     6,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,     6,   424,   538,   386,   427,  -321,  -321,
     144,  -321,  -321,   439,   431,   430,   265,   432,   538,  -321,
     440,   441,   445,  -321,   473,  -321,  -321,  -321,  -321,   454,
     456,   319,   136,   144,   498,  -321,   144,  -321,   319,   335,
     319,   319,   444,   453,  -321,  -321,   484,   381,  -321,   458,
    -321,   538,   457,  -321,   464,   538,  -321,   256,  -321,  -321,
    -321,   510,  -321,  -321,   192,    11,   462,  -321,   468,   469,
     472,   489,   492,   493,  -321,  -321,  -321,    49,   247,   174,
     538,   431,  -321,   471,   499,   422,   445,  -321,   136,   494,
     495,  -321,   186,   444,   497,  -321,  -321,   473,    26,   473,
    -321,   515,   513,  -321,   504,   422,   522,  -321,  -321,   318,
     422,   534,   528,   521,   572,  -321,   193,   524,   254,   174,
     473,   422,   529,  -321,    99,   530,  -321,  -321,   444,   444,
     531,   532,  -321,  -321,   160,   535,  -321,   536,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,   498,  -321
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      23,     0,     4,     2,     3,     0,     0,    23,     0,     0,
       1,    24,     0,     0,     0,     0,    33,     0,    31,    32,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,     7,     6,     5,     0,
       0,     0,    15,    16,    20,    21,    22,   129,    17,    18,
       0,     0,     0,     0,     0,     0,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   137,
     136,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
       0,     0,    41,     0,     0,     0,    44,     0,     0,     0,
       0,     0,    41,     0,     0,   122,   134,    94,    90,    88,
      91,    95,    96,    26,    93,    89,    19,     0,   141,   135,
       0,     0,   121,     0,     0,   128,    92,     0,    33,     0,
       0,     0,     0,     0,   124,    54,    55,    56,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,     0,     0,
      39,    58,   133,     0,     0,     0,    82,    36,     0,   143,
       0,   126,   127,   138,   139,    28,    34,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
      67,     0,   106,   107,   104,   101,   100,    98,   105,    73,
     103,    99,   102,     0,     0,    82,     0,     0,   145,    43,
      42,   131,   130,     0,    47,     0,    44,     0,    82,    35,
       0,     0,    85,   118,     0,   142,   140,    30,    27,     0,
       0,    56,     0,    53,    79,    76,    68,    66,    56,    69,
      56,    56,     0,     0,   119,   120,     0,     0,    40,     0,
      45,    82,     0,    84,     0,     0,    83,   143,    29,   111,
      57,    49,    52,    51,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,    59,    65,    64,     0,     0,     0,
       0,    47,    37,     0,     0,     0,    85,   144,     0,     0,
       0,    77,     0,     0,     0,   116,   117,     0,     0,     0,
     115,    75,     0,    48,     0,     0,     0,    86,    50,     0,
       0,     0,     0,     0,    62,    60,     0,     0,     0,     0,
       0,     0,     0,   110,    79,     0,    71,    72,     0,     0,
       0,     0,   112,    74,     0,     0,   109,     0,    81,    78,
      61,    63,   113,   114,    46,   108,    79,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -321,   154,   537,   -49,   281,   263,   314,   584,  -321,   575,
     576,   -68,   -18,   -34,   425,   369,   339,   306,  -321,   300,
     -75,  -130,   -27,    -3,  -321,  -296,  -321,  -133,  -191,  -321,
     -26,    51,  -321,  -321,  -320,  -202,   336,   303,    41,   418,
      97,  -321,   -78,   -39,   -23,   -98,    84,  -321,  -321,  -321,
     333,   106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    52,    53,    54,    55,   119,    56,     6,     7,    15,
      16,    74,    57,    95,    96,   170,   224,   258,    58,   271,
     137,   193,    59,    60,   149,   284,   142,   143,   200,   323,
     150,    61,    62,   245,   275,   231,   232,   266,    63,   152,
      64,   286,    65,    66,    67,    68,    69,   125,    70,   180,
     235,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    86,    90,   100,   101,   154,   247,   324,   197,   132,
     157,    22,    90,   253,   348,    12,   106,    13,    91,     8,
     104,   300,   181,   182,   135,   136,   262,   214,    98,   163,
      14,    22,   164,   141,   165,     9,   357,    10,   120,   121,
     176,    90,   350,   351,   166,   172,    90,    43,    90,   160,
     173,    44,    45,    46,    89,    48,    49,   138,   277,   293,
     186,    51,   138,   301,   159,   147,   249,   175,    17,   154,
     154,   154,   154,   154,   105,   154,   154,   154,    90,    90,
     148,    90,    90,   116,    90,    90,   117,   120,   121,    73,
     116,    97,   122,   309,   178,   179,   116,   118,   107,   108,
     109,   110,   111,   112,   118,   114,   115,    12,   274,    13,
     118,   270,   126,   127,   347,    18,   130,   241,   276,    72,
     278,   279,    75,   248,    90,    19,   250,   230,    78,   147,
     147,   147,   147,   147,   151,   147,   147,   147,   251,    79,
     220,    22,   123,   124,   148,   148,   148,   148,   148,   102,
     148,   148,   148,    90,     5,    90,    92,    90,   103,    90,
      80,     5,    90,    83,   273,   103,   230,    39,    40,   138,
     187,   243,   189,   246,    90,   138,    81,    43,   138,   230,
     153,    44,    45,    46,    89,    48,    49,    50,    82,   155,
     138,    51,     1,   120,   121,    90,   120,   121,   151,   151,
     151,   151,   151,   216,   151,   151,   151,   183,   184,   120,
     121,   267,   230,   287,  -122,   272,   230,  -122,   354,    85,
     273,    92,     2,     3,     4,    50,   285,    43,  -122,   288,
      93,   239,   240,    94,   321,    48,    49,    44,    45,    46,
      87,   312,   120,   121,   153,   153,   153,   153,   153,   340,
     153,   153,   153,   155,   155,   155,   155,   155,   194,   155,
     155,   155,   311,    88,   287,   120,   121,   113,    90,   327,
      90,   272,   128,  -122,   120,   121,  -122,   285,   129,   162,
     288,   164,   131,   165,   326,   133,   328,  -122,   134,   161,
     139,    90,    94,   120,   121,   156,   120,   121,   233,   287,
     287,   310,   343,   120,   121,   120,   121,   344,   342,   234,
     158,   163,   285,   285,   167,   288,   288,   168,   169,    20,
     171,   174,    21,    22,    23,   177,    24,   -87,   -87,    25,
      26,    27,   166,   -87,    28,    94,   316,   185,    29,    30,
      31,    32,    33,    34,    35,   190,    36,    37,    38,    39,
      40,     2,     3,     4,   188,   191,   332,    41,    42,    43,
     334,   335,   192,    44,    45,    46,    47,    48,    49,    50,
     -87,    20,   345,    51,    21,    22,   144,   195,   196,   140,
     198,    25,    26,    27,   145,   146,    28,   201,   199,   209,
      29,    30,    31,    32,    33,    34,    35,   202,    36,    37,
      38,    39,    40,     2,     3,     4,   203,   217,   213,    41,
      42,    43,   215,   218,   221,    44,    45,    46,    47,    48,
      49,    83,   -97,    20,   222,    51,    21,    22,    23,   223,
      24,   225,    92,    25,    26,    27,   227,   228,    28,   229,
     254,   237,    29,    30,    31,    32,    33,    34,    35,    22,
      36,    37,    38,    39,    40,     2,     3,     4,   280,   281,
      22,    41,    42,    43,   236,   238,   242,    44,    45,    46,
      47,    48,    49,    50,   -87,   282,   283,    51,    22,   244,
     252,   255,   219,   256,   257,    43,   259,   261,   263,    44,
      45,    46,    89,    48,    49,    83,    43,   264,   265,    51,
      44,    45,    46,    89,    48,    49,   268,   274,   269,   289,
      51,   290,   292,   294,    43,   295,   302,   298,    44,    45,
      46,    89,    48,    49,   303,   304,   305,   314,    51,    29,
      30,    31,    32,    33,    34,    35,    29,    30,    31,    32,
      33,    34,    35,   306,    36,    37,    38,   307,   308,    42,
     315,   325,   329,   319,   320,   331,    42,   140,    29,    30,
      31,    32,    33,    34,    35,   204,   205,   206,   207,   208,
     330,   210,   211,   212,   333,   116,   337,   338,    42,   339,
     341,   346,   349,   322,   336,   352,   353,   355,   299,    99,
     356,    11,    76,    77,   226,   260,   291,   313,   318,   317,
     297,   296
};

static const yytype_uint16 yycheck[] =
{
      26,    28,    41,    52,    53,    83,   197,   303,   141,    77,
      85,     5,    51,   215,   334,    36,    55,    38,    41,    48,
      54,    10,   120,   121,    18,    19,   228,   157,    51,    44,
      51,     5,    46,    82,    48,     3,   356,     0,    49,    50,
      55,    80,   338,   339,    58,    56,    85,    41,    87,    88,
      99,    45,    46,    47,    48,    49,    50,    80,   249,   261,
     128,    55,    85,    52,    87,    83,   199,   101,    48,   147,
     148,   149,   150,   151,    48,   153,   154,   155,   117,   118,
      83,   120,   121,    41,   123,   124,    44,    49,    50,    53,
      41,    50,    54,    44,   117,   118,    41,    55,    57,    58,
      59,    60,    61,    62,    55,    64,    65,    36,     9,    38,
      55,   241,    71,    72,    15,    48,    75,   192,   248,    51,
     250,   251,    51,   198,   163,    48,   201,   176,    55,   147,
     148,   149,   150,   151,    83,   153,   154,   155,   213,    60,
     163,     5,    61,    62,   147,   148,   149,   150,   151,    48,
     153,   154,   155,   192,     0,   194,    48,   196,    57,   198,
      55,     7,   201,    51,   242,    57,   215,    31,    32,   192,
     129,   194,   131,   196,   213,   198,    55,    41,   201,   228,
      83,    45,    46,    47,    48,    49,    50,    51,    55,    83,
     213,    55,     3,    49,    50,   234,    49,    50,   147,   148,
     149,   150,   151,    56,   153,   154,   155,   123,   124,    49,
      50,   234,   261,   252,    41,   242,   265,    44,    58,    55,
     298,    48,    33,    34,    35,    51,   252,    41,    55,   252,
      57,   190,   191,    60,    48,    49,    50,    45,    46,    47,
      55,   290,    49,    50,   147,   148,   149,   150,   151,    56,
     153,   154,   155,   147,   148,   149,   150,   151,    42,   153,
     154,   155,   289,    55,   303,    49,    50,    52,   307,   308,
     309,   298,    48,    41,    49,    50,    44,   303,    51,    54,
     303,    46,    51,    48,   307,    56,   309,    55,    48,    57,
      48,   330,    60,    49,    50,    13,    49,    50,    54,   338,
     339,    54,   329,    49,    50,    49,    50,   330,    54,    53,
      17,    44,   338,   339,    48,   338,   339,    48,    53,     1,
      52,    48,     4,     5,     6,    54,     8,     9,    10,    11,
      12,    13,    58,    15,    16,    60,   295,    52,    20,    21,
      22,    23,    24,    25,    26,    51,    28,    29,    30,    31,
      32,    33,    34,    35,    52,    51,   315,    39,    40,    41,
     319,   320,    43,    45,    46,    47,    48,    49,    50,    51,
      52,     1,   331,    55,     4,     5,     6,    56,    44,    48,
      54,    11,    12,    13,    14,    15,    16,    55,    53,    52,
      20,    21,    22,    23,    24,    25,    26,    54,    28,    29,
      30,    31,    32,    33,    34,    35,    54,    56,    55,    39,
      40,    41,    55,    63,    58,    45,    46,    47,    48,    49,
      50,    51,    52,     1,    58,    55,     4,     5,     6,    48,
       8,    55,    48,    11,    12,    13,    48,    55,    16,    54,
      54,    52,    20,    21,    22,    23,    24,    25,    26,     5,
      28,    29,    30,    31,    32,    33,    34,    35,    14,    15,
       5,    39,    40,    41,    56,    52,    56,    45,    46,    47,
      48,    49,    50,    51,    52,    31,    32,    55,     5,    51,
      56,    54,    27,    44,    53,    41,    56,    55,    48,    45,
      46,    47,    48,    49,    50,    51,    41,    56,    53,    55,
      45,    46,    47,    48,    49,    50,    52,     9,    52,    56,
      55,    27,    54,    56,    41,    51,    54,     7,    45,    46,
      47,    48,    49,    50,    56,    56,    54,    56,    55,    20,
      21,    22,    23,    24,    25,    26,    20,    21,    22,    23,
      24,    25,    26,    54,    28,    29,    30,    55,    55,    40,
      51,    54,    37,    59,    59,    51,    40,    48,    20,    21,
      22,    23,    24,    25,    26,   147,   148,   149,   150,   151,
      57,   153,   154,   155,    52,    41,    48,    56,    40,     7,
      56,    52,    52,   302,   321,    54,    54,    52,   274,    52,
      54,     7,    17,    17,   169,   226,   257,   291,   298,   296,
     267,   265
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    33,    34,    35,    65,    71,    72,    48,     3,
       0,    71,    36,    38,    51,    73,    74,    48,    48,    48,
       1,     4,     5,     6,     8,    11,    12,    13,    16,    20,
      21,    22,    23,    24,    25,    26,    28,    29,    30,    31,
      32,    39,    40,    41,    45,    46,    47,    48,    49,    50,
      51,    55,    65,    66,    67,    68,    70,    76,    82,    86,
      87,    95,    96,   102,   104,   106,   107,   108,   109,   110,
     112,   115,    51,    53,    75,    51,    73,    74,    55,    60,
      55,    55,    55,    51,    94,    55,    86,    55,    55,    48,
     107,   108,    48,    57,    60,    77,    78,   102,   108,    66,
      67,    67,    48,    57,    77,    48,   107,   102,   102,   102,
     102,   102,   102,    52,   102,   102,    41,    44,    55,    69,
      49,    50,    54,    61,    62,   111,   102,   102,    48,    51,
     102,    51,    75,    56,    48,    18,    19,    84,   108,    48,
      48,    67,    90,    91,     6,    14,    15,    76,    87,    88,
      94,    95,   103,   104,   106,   115,    13,    84,    17,   108,
     107,    57,    54,    44,    46,    48,    58,    48,    48,    53,
      79,    52,    56,    67,    48,    77,    55,    54,   108,   108,
     113,   109,   109,   110,   110,    52,    75,   102,    52,   102,
      51,    51,    43,    85,    42,    56,    44,    91,    54,    53,
      92,    55,    54,    54,   103,   103,   103,   103,   103,    52,
     103,   103,   103,    55,    85,    55,    56,    56,    63,    27,
     108,    58,    58,    48,    80,    55,    78,    48,    55,    54,
      67,    99,   100,    54,    53,   114,    56,    52,    52,   102,
     102,    84,    56,   108,    51,    97,   108,    92,    84,    91,
      84,    84,    56,    99,    54,    54,    44,    53,    81,    56,
      79,    55,    99,    48,    56,    53,   101,   108,    52,    52,
      85,    83,    86,   106,     9,    98,    85,    92,    85,    85,
      14,    15,    31,    32,    89,    94,   105,   107,   108,    56,
      27,    80,    54,    99,    56,    51,   100,   114,     7,    70,
      10,    52,    54,    56,    56,    54,    54,    55,    55,    44,
      54,    86,    67,    81,    56,    51,   102,   101,    83,    59,
      59,    48,    68,    93,    89,    54,   108,   107,   108,    37,
      57,    51,   102,    52,   102,   102,    69,    48,    56,     7,
      56,    56,    54,    86,   108,   102,    52,    15,    98,    52,
      89,    89,    54,    54,    58,    52,    54,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    68,    69,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    75,    76,    76,    76,    76,    77,
      77,    78,    78,    78,    79,    79,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    84,    85,    85,    86,    87,
      87,    87,    88,    88,    89,    89,    90,    90,    91,    92,
      92,    93,    93,    94,    95,    95,    96,    97,    97,    98,
      98,    98,    99,    99,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   104,   105,   105,   105,   105,   105,   105,   106,   106,
     106,   106,   107,   107,   107,   108,   108,   108,   109,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111,   111,
     112,   113,   113,   114,   114,   115
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     6,     5,     7,     6,     8,
       7,     2,     2,     0,     3,     4,     3,     6,     1,     2,
       4,     1,     3,     3,     0,     3,     7,     0,     3,     6,
       8,     1,     1,     3,     1,     1,     0,     3,     3,     6,
       8,    10,     6,     8,     1,     1,     3,     2,     3,     0,
       3,     2,     2,     3,     9,     7,     5,     3,     6,     0,
       7,     5,     0,     2,     2,     0,     3,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    10,     9,
       8,     6,     4,     5,     5,     2,     2,     2,     4,     5,
       5,     2,     1,     3,     3,     1,     3,     3,     2,     1,
       4,     4,     1,     3,     2,     2,     1,     0,     2,     2,
       4,     0,     2,     0,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 41:
#line 142 "B033040006.y" /* yacc.c:1646  */
    { duplicate(id_name); }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 143 "B033040006.y" /* yacc.c:1646  */
    { duplicate(id_name); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 144 "B033040006.y" /* yacc.c:1646  */
    { duplicate(id_name); }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 157 "B033040006.y" /* yacc.c:1646  */
    { duplicate(id_name); }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1653 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 400 "B033040006.y" /* yacc.c:1906  */


int main()
{
	creat();
	yyparse();
	return 0;
}

void yyerror(char *str)
{
	mistake = 1;
	sprintf(error_msg2,"> ERROR : Line %d at %d [%s] has %s. \n", line, position-yyleng+1, yytext, str);
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
		sprintf(error_msg,"> ERROR : Line %d at %d \'%s\' is a duplicate identifier.\n", line-yyleng, position, s);
	}
}
