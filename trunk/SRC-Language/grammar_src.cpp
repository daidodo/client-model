#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20080827

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
#ifdef YYPARSE_PARAM_TYPE
#define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
#else
#define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
#endif
#else
#define YYPARSE_DECL() yyparse(void)
#endif /* YYPARSE_PARAM */

extern int YYPARSE_DECL();

static int yygrowstack(void);
#define YYPREFIX "yy"

#include "global.h"
#include "dbg.h"
#include "yystype.h"
#include "yyhack.h"

int yylex();
#define NL 257
#define EOF_ 258
#define IEQ 259
#define CMD 260
#define DEF 261
#define TP_U8 262
#define TP_S8 263
#define TP_U16 264
#define TP_S16 265
#define TP_U32 266
#define TP_S32 267
#define TP_U64 268
#define TP_S64 269
#define STR 270
#define RAW 271
#define TCP 272
#define UDP 273
#define FUN 274
#define BEGIN_ 275
#define END 276
#define HBO 277
#define NBO 278
#define SEND 279
#define RECV 280
#define HEX 281
#define UNHEX 282
#define PRINT 283
#define IP 284
#define __IPN 285
#define __IPH 286
#define ARRAY 287
#define __END_ARRAY 288
#define SLEEP 289
#define OP_LG 290
#define OP_SM 291
#define OP_LEQ 292
#define OP_SEQ 293
#define OP_EQ 294
#define OP_NEQ 295
#define OP_NOT 296
#define OP_IN 297
#define OP_OUT 298
#define INT 299
#define LONG 300
#define I64 301
#define QSTRING 302
#define VAR_NAME 303
#define PROG_ARG 304
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   20,   20,   21,   21,   21,   22,   24,   24,
   26,   26,   26,   25,   25,   27,   12,   12,   12,   12,
   12,   12,   19,   19,   19,   11,   11,   13,   14,   14,
   15,   15,   15,   16,   17,   17,   18,   18,    9,    9,
   10,   10,    8,    8,    6,    7,    7,    7,    5,    5,
    5,    5,    5,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    3,    3,    3,    3,    3,    3,    3,    4,    4,   23,
   23,   23,
};
static const short yylen[] = {                            2,
    0,    2,    1,    1,    1,    2,    2,    4,    1,    2,
    1,    2,    2,    1,    2,    2,    1,    1,    1,    1,
    1,    1,    1,    4,    4,    3,    2,    2,    3,    5,
    1,    3,    4,    3,    3,    3,    2,    2,    0,    1,
    1,    3,    3,    4,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    2,    2,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,
};
static const short yydefred[] = {                         1,
    0,   91,   92,    0,    0,   69,   70,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   54,    0,    0,
   57,   58,   59,   60,   61,   62,   63,    0,   68,   90,
    0,    0,    0,    0,    0,   17,   18,   19,   20,   21,
   22,    9,    2,    3,    4,    5,    0,    0,   15,    0,
    0,   37,   38,   66,   67,   65,   64,   45,    0,    0,
    0,    0,   81,   82,   83,   84,   85,   86,   87,   88,
   89,    0,    0,    0,    0,    0,   28,    7,    0,   10,
    6,   11,    0,   49,   50,   51,   52,   48,   53,   46,
   41,    0,    0,   47,   43,    0,    0,   29,    0,    0,
   32,   34,    0,   35,    0,    0,    0,   13,    0,   12,
    0,   25,    0,   44,   24,   33,    0,   16,   27,    0,
    8,   42,   30,   26,
};
static const short yydgoto[] = {                          1,
   79,   32,   75,   76,   90,   33,   91,   34,   92,   93,
  108,   35,   36,   37,   38,   39,   40,   41,   94,   43,
   44,   45,   46,   47,   48,   83,  111,
};
static const short yysindex[] = {                         0,
  283,    0,    0, -289, -160,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -270, -264,
    0,    0,    0,    0,    0,    0,    0, -257,    0,    0,
  -35,  -16,   82, -278,  -57,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  378,  312,    0, -277,
  -11,    0,    0,    0,    0,    0,    0,    0,  469,  426,
  469,  469,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  469,  -13,  469,  469,  469,    0,    0,  -12,    0,
    0,    0,  186,    0,    0,    0,    0,    0,    0,    0,
    0,   -7,   -9,    0,    0,  -55,   -1,    0,    1,  469,
    0,    0,  -12,    0, -251,  469, -167,    0,    0,    0,
  -57,    0,  469,    0,    0,    0,    2,    0,    0,  469,
    0,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,  350,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -40,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   56,  -53,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -53,    0,    0,    0,    0,    0,    0,    0,    3,    0,
    3,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    5,    0,    0,    0,    0,    0,    0,    3,
    0,    0,  -51,    0,  124,    0,    0,    0,  234,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    6,    0,  -70,    0,    0,   36,  -44,    0,  -39,    0,
    0,    0,    0,   46,   50,    0,    0,    0,   11,    0,
  -38,    0,  -32,    0,    0,    0,    0,
};
#define YYTABLESIZE 773
static const short yytable[] = {                         55,
   55,   30,   78,   55,   59,   31,   31,   36,  118,   82,
   50,   42,  106,   49,   81,   96,   54,   98,   55,   56,
   57,   97,   55,   61,   77,   58,  100,   59,   72,  101,
  102,  104,   99,  112,  113,   55,  120,  114,  107,  115,
   51,  116,  123,   39,  110,   40,   73,   56,   56,   74,
   52,   56,   55,   31,   53,   60,    0,   80,   42,    0,
  117,  119,    0,    0,    0,    0,   56,    0,  122,    0,
    0,    0,    0,    0,    0,  124,    0,    0,  121,    0,
    0,  103,    0,    0,    0,    0,    0,    0,   31,    0,
    0,    0,    0,  109,    0,    0,   23,    0,    0,   23,
   56,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,    0,   23,    0,    0,    0,    0,    0,
    0,   72,   63,   64,   65,   66,   67,   68,   69,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   73,
    0,    0,   74,    0,    0,    0,    0,    0,   23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   56,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    2,
    3,    0,    0,   31,   31,   36,   36,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   55,   55,    0,    0,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
   55,   55,   55,   55,   30,    0,    0,   62,   55,   55,
   55,   55,   55,   55,   55,   55,    0,    0,   55,   55,
   55,   55,   55,   55,   56,   56,    0,   58,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   56,    9,    0,    0,    0,   56,   56,   56,   56,
   56,   56,   56,   56,    0,    0,   56,   56,   56,   56,
   56,   56,   23,   23,    0,    0,   23,   23,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
   62,   30,    0,    0,   23,   23,   23,   23,   23,   23,
   23,   23,    0,    0,   23,   23,   23,   23,   23,   23,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   30,   63,   64,   65,   66,   67,   68,   69,   70,   71,
   56,   56,    0,    0,    0,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   14,    0,
    0,    0,   56,   56,   56,   56,   56,   56,   56,   56,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   30,    0,    0,    0,
    0,    0,    2,    3,    0,    0,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,  105,   21,   22,   23,   24,   25,   26,   27,   28,
    0,    0,    0,    0,   29,   63,   64,   65,   66,   67,
   68,   69,    0,    0,   84,   85,   86,   87,   88,   89,
    9,    9,    0,    0,    0,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,   95,    0,
    0,    0,    9,   47,   47,   47,   47,   47,   47,   47,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    2,
    3,    0,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   24,   25,   26,   27,   28,    0,    2,    3,
    0,   29,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
   23,   24,   25,   26,   27,   28,    0,    0,    0,    0,
   29,    0,    0,    0,    0,    0,   14,   14,    0,    0,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,    2,    3,    0,    0,   14,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
   27,   28,    0,    0,    0,    0,   29,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
    0,    0,    0,    0,   29,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   84,   85,   86,   87,   88,   89,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
   26,   27,   28,    0,    0,    0,    0,   29,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   84,   85,   86,
   87,   88,   89,
};
static const short yycheck[] = {                         40,
   41,   59,   35,   44,   40,   59,    1,   59,  260,   48,
    5,    1,   83,  303,   47,   60,  287,   62,   59,  277,
  278,   61,  287,   40,  303,  303,   40,   40,   40,   74,
   75,   76,   72,   41,   44,  287,  107,   93,   83,   41,
    5,   41,   41,   41,   83,   41,   58,   40,   41,   61,
    5,   44,   93,   48,    5,   91,   -1,   47,   48,   -1,
  100,  106,   -1,   -1,   -1,   -1,   59,   -1,  113,   -1,
   -1,   -1,   -1,   -1,   -1,  120,   -1,   -1,  111,   -1,
   -1,   76,   -1,   -1,   -1,   -1,   -1,   -1,   83,   -1,
   -1,   -1,   -1,   83,   -1,   -1,   41,   -1,   -1,   44,
   93,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,   -1,   59,   -1,   -1,   -1,   -1,   -1,
   -1,   40,  290,  291,  292,  293,  294,  295,  296,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,
   -1,   -1,   61,   -1,   -1,   -1,   -1,   -1,   93,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   40,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,   -1,   -1,  257,  258,  257,  258,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,   59,   -1,   -1,  259,  289,  290,
  291,  292,  293,  294,  295,  296,   -1,   -1,  299,  300,
  301,  302,  303,  304,  257,  258,   -1,  303,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,   59,   -1,   -1,   -1,  289,  290,  291,  292,
  293,  294,  295,  296,   -1,   -1,  299,  300,  301,  302,
  303,  304,  257,  258,   -1,   -1,  261,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  259,   59,   -1,   -1,  289,  290,  291,  292,  293,  294,
  295,  296,   -1,   -1,  299,  300,  301,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   59,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  257,  258,   -1,   -1,   -1,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,   59,   -1,
   -1,   -1,  289,  290,  291,  292,  293,  294,  295,  296,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,
   -1,   -1,  257,  258,   -1,   -1,  261,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
   -1,   -1,   -1,   -1,  289,  290,  291,  292,  293,  294,
  295,  296,   -1,   -1,  299,  300,  301,  302,  303,  304,
  257,  258,   -1,   -1,   -1,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,   93,   -1,
   -1,   -1,  289,  290,  291,  292,  293,  294,  295,  296,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,   -1,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,   -1,  257,  258,
   -1,  289,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,  283,  284,   -1,   -1,   -1,   -1,
  289,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  257,  258,   -1,   -1,  289,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,   -1,   -1,   -1,   -1,  289,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
   -1,   -1,   -1,   -1,  289,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  299,  300,  301,  302,  303,  304,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  284,   -1,   -1,   -1,   -1,  289,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  299,  300,  301,
  302,  303,  304,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 304
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"NL","EOF_","IEQ","CMD","DEF","TP_U8","TP_S8","TP_U16","TP_S16","TP_U32",
"TP_S32","TP_U64","TP_S64","STR","RAW","TCP","UDP","FUN","BEGIN_","END","HBO",
"NBO","SEND","RECV","HEX","UNHEX","PRINT","IP","__IPN","__IPH","ARRAY",
"__END_ARRAY","SLEEP","OP_LG","OP_SM","OP_LEQ","OP_SEQ","OP_EQ","OP_NEQ",
"OP_NOT","OP_IN","OP_OUT","INT","LONG","I64","QSTRING","VAR_NAME","PROG_ARG",
};
static const char *yyrule[] = {
"$accept : program",
"program :",
"program : program program_item",
"program_item : stmt",
"program_item : cmd_define",
"stmt : stmt_sep",
"stmt : func_call_list stmt_sep",
"stmt : declare stmt_sep",
"cmd_define : cmd_begin stmt_assert_list cmd_end stmt_sep",
"func_call_list : func_call",
"func_call_list : func_call_list func_call",
"stmt_assert_list : stmt",
"stmt_assert_list : stmt_assert_list stmt",
"stmt_assert_list : stmt_assert_list assert_exp",
"cmd_begin : CMD",
"cmd_begin : CMD VAR_NAME",
"cmd_end : END CMD",
"declare : array_declare",
"declare : constant_declare",
"declare : post_declare",
"declare : assert_declare",
"declare : stream_declare",
"declare : define_declare",
"func_call : func_name",
"func_call : func_name '(' arg_list ')'",
"func_call : simple_type '(' arg_list ')'",
"assert_exp : expr comp_op expr",
"assert_exp : comp_op expr",
"array_declare : array_type VAR_NAME",
"constant_declare : sim_type_name IEQ expr",
"constant_declare : sim_type_name ':' '(' arg_list ')'",
"post_declare : sim_type_name",
"post_declare : sim_type_name '=' expr",
"post_declare : sim_type_name '(' arg_list ')'",
"assert_declare : sim_type_name comp_op expr",
"stream_declare : sim_type_name stream_op expr",
"stream_declare : sim_type_name stream_op simple_type",
"define_declare : DEF constant_declare",
"define_declare : DEF post_declare",
"arg_list :",
"arg_list : arg_list_not_empty",
"arg_list_not_empty : expr",
"arg_list_not_empty : arg_list_not_empty ',' expr",
"array_type : simple_type '[' ']'",
"array_type : simple_type '[' expr ']'",
"sim_type_name : simple_type VAR_NAME",
"expr : fix_value",
"expr : func_call",
"expr : VAR_NAME",
"fix_value : INT",
"fix_value : LONG",
"fix_value : I64",
"fix_value : QSTRING",
"fix_value : PROG_ARG",
"func_name : FUN",
"func_name : BEGIN_",
"func_name : END",
"func_name : HBO",
"func_name : NBO",
"func_name : SEND",
"func_name : RECV",
"func_name : HEX",
"func_name : UNHEX",
"func_name : PRINT",
"func_name : IP NBO",
"func_name : IP HBO",
"func_name : BEGIN_ ARRAY",
"func_name : END ARRAY",
"func_name : SLEEP",
"simple_type : TP_U8",
"simple_type : TP_S8",
"simple_type : TP_U16",
"simple_type : TP_S16",
"simple_type : TP_U32",
"simple_type : TP_S32",
"simple_type : TP_U64",
"simple_type : TP_S64",
"simple_type : STR",
"simple_type : RAW",
"simple_type : TCP",
"simple_type : UDP",
"comp_op : OP_LG",
"comp_op : OP_SM",
"comp_op : OP_LEQ",
"comp_op : OP_SEQ",
"comp_op : OP_EQ",
"comp_op : OP_NEQ",
"comp_op : OP_NOT",
"stream_op : OP_IN",
"stream_op : OP_OUT",
"stmt_sep : ';'",
"stmt_sep : NL",
"stmt_sep : EOF_",

};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static unsigned yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    yystate = 0;
    *yyssp = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yyssp = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yyssp = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
	{DBG_YY("program 1");}
break;
case 2:
	{DBG_YY("program 2");}
break;
case 3:
	{DBG_YY("program_item 1");}
break;
case 4:
	{DBG_YY("program_item 2");}
break;
case 5:
	{DBG_YY("stmt 1");}
break;
case 6:
	{DBG_YY("stmt 2");}
break;
case 7:
	{DBG_YY("stmt 3");}
break;
case 8:
	{DBG_YY("cmd_define 1");}
break;
case 9:
	{
				DBG_YY("func_call_list 1 ");
				DBG_YY("$1 = "<<to_str(yyvsp[0].func_call_));
				program().AddStmt(yyvsp[0].func_call_);
			}
break;
case 10:
	{
				DBG_YY("func_call_list 2");
				DBG_YY("$2 = "<<to_str(yyvsp[0].func_call_));
				program().AddStmt(yyvsp[0].func_call_);
			}
break;
case 11:
	{DBG_YY("stmt_list 1");}
break;
case 12:
	{DBG_YY("stmt_list 2");}
break;
case 13:
	{DBG_YY("stmt_list 3");}
break;
case 14:
	{DBG_YY("cmd_begin 1");program().CmdBegin(0);}
break;
case 15:
	{DBG_YY("cmd_begin 2");program().CmdBegin(yyvsp[0].var_);}
break;
case 16:
	{
				DBG_YY("cmd_end");
				assert(CUR_CMD);
				CUR_CMD->endlineno_ = LINE_NO;
				program().CmdEnd();
			}
break;
case 17:
	{
				DBG_YY("declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 18:
	{
				DBG_YY("declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 19:
	{
				DBG_YY("declare 3");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 20:
	{
				DBG_YY("declare 4");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 21:
	{
				DBG_YY("declare 5");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 22:
	{
				DBG_YY("declare 6");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 23:
	{
				DBG_YY("func_call 1");
				DBG_YY("$1 = "<<yyvsp[0].token_);
				yyval.func_call_ = New<CFuncCall>(LINE_NO);
				yyval.func_call_->ft_token_ = yyvsp[0].token_;
				DBG_YY("$$ = "<<to_str(yyval.func_call_));
			}
break;
case 24:
	{
				DBG_YY("func_call 2");
				DBG_YY("$1 = "<<yyvsp[-3].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[-1].arg_list_));
				yyval.func_call_ = New<CFuncCall>(LINE_NO);
				yyval.func_call_->ft_token_ = yyvsp[-3].token_;
				yyval.func_call_->arg_list_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.func_call_));
			}
break;
case 25:
	{
				DBG_YY("func_call 3");
				DBG_YY("$1 = "<<yyvsp[-3].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[-1].arg_list_));
				yyval.func_call_ = New<CFuncCall>(LINE_NO);
				yyval.func_call_->ft_token_ = yyvsp[-3].token_;
				yyval.func_call_->arg_list_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.func_call_));
			}
break;
case 26:
	{
				DBG_YY("assert_exp 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].expr_));
				DBG_YY("$2 = "<<yyvsp[-1].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				yyval.assert_exp_ = New<CAssertExp>(LINE_NO);
				yyval.assert_exp_->op_token_ = yyvsp[-1].token_;
				yyval.assert_exp_->expr1_ = yyvsp[-2].expr_;
				yyval.assert_exp_->expr2_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.assert_exp_));
				program().AddStmt(yyval.assert_exp_);
			}
break;
case 27:
	{
				DBG_YY("assert_exp 2");
				DBG_YY("$1 = "<<yyvsp[-1].token_);
				DBG_YY("$2 = "<<to_str(yyvsp[0].expr_));
				yyval.assert_exp_ = New<CAssertExp>(LINE_NO);
				yyval.assert_exp_->op_token_ = yyvsp[-1].token_;
				yyval.assert_exp_->expr1_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.assert_exp_));
				program().AddStmt(yyval.assert_exp_);
			}
break;
case 28:
	{
				DBG_YY("array_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-1].array_type_));
				DBG_YY("$2 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[-1].array_type_ && yyvsp[0].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[-1].array_type_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[0].var_;
				if(yyval.declare_->var_->ref_count_ > 0){
					/*redefinition, but we need the whole declaration*/
					CSharedPtr<CVariable> t = yyval.declare_->var_;
					yyval.declare_->var_ = New<CVariable>(LINE_NO);
					yyval.declare_->var_->shadow_ = t;
					yyval.declare_->var_->varname_ = t->varname_;
					yyval.declare_->var_->host_cmd_ = CUR_CMD;
				}
				yyval.declare_->var_->array_type_ = yyvsp[-1].array_type_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 29:
	{
				DBG_YY("constant_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 5;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->expr_ = New<CExpr>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ = New<CFuncCall>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[-2].var_->tp_token_;
				yyval.declare_->expr_->func_call_->arg_list_ = New<CArgList>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->func_call_->arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 30:
	{
				DBG_YY("constant_declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[-4].var_));
				DBG_YY("$4 = "<<to_str(yyvsp[-1].arg_list_));
				assert(yyvsp[-4].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[-4].var_->lineno_);
				yyval.declare_->type_ = 6;
				yyval.declare_->var_ = yyvsp[-4].var_;
				yyval.declare_->expr_ = New<CExpr>(LINE_NO);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ =  New<CFuncCall>(LINE_NO);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[-4].var_->tp_token_;
				yyval.declare_->expr_->func_call_->arg_list_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 31:
	{
				DBG_YY("post_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[0].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[0].var_->lineno_);
				yyval.declare_->type_ = 2;
				yyval.declare_->var_ = yyvsp[0].var_;
				yyval.declare_->expr_ = New<CExpr>(yyvsp[0].var_->lineno_);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ = New<CFuncCall>(yyvsp[0].var_->lineno_);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[0].var_->tp_token_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 32:
	{
				DBG_YY("post_declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 3;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->expr_ = New<CExpr>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ = New<CFuncCall>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[-2].var_->tp_token_;
				yyval.declare_->expr_->func_call_->arg_list_ = New<CArgList>(yyvsp[-2].var_->lineno_);
				yyval.declare_->expr_->func_call_->arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 33:
	{
				DBG_YY("post_declare 3");
				DBG_YY("$1 = "<<to_str(yyvsp[-3].var_));
				DBG_YY("$3 = "<<to_str(yyvsp[-1].arg_list_));
				assert(yyvsp[-3].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[-3].var_->lineno_);
				yyval.declare_->type_ = 4;
				yyval.declare_->var_ = yyvsp[-3].var_;
				yyval.declare_->expr_ = New<CExpr>(LINE_NO);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ =  New<CFuncCall>(LINE_NO);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[-3].var_->tp_token_;
				yyval.declare_->expr_->func_call_->arg_list_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 34:
	{
				DBG_YY("assert_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$2 = "<<yyvsp[-1].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 7;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->op_token_ = yyvsp[-1].token_;
				yyval.declare_->expr_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 35:
	{
				DBG_YY("stream_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$2 = "<<yyvsp[-1].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 8;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->op_token_ = yyvsp[-1].token_;
				yyval.declare_->expr_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 36:
	{
				DBG_YY("stream_declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$2 = "<<yyvsp[-1].token_);
				DBG_YY("$3 = "<<yyvsp[0].token_);
				assert(yyvsp[-2].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 9;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->op_token_ = yyvsp[-1].token_;
				yyval.declare_->expr_ = New<CExpr>(LINE_NO);
				yyval.declare_->expr_->type_ = 2;
				yyval.declare_->expr_->func_call_ =  New<CFuncCall>(LINE_NO);
				yyval.declare_->expr_->func_call_->ft_token_ = yyvsp[0].token_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 37:
	{
				DBG_YY("define_declare 1");
				DBG_YY("$2 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				yyval.declare_->is_def_ = 1;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 38:
	{
				DBG_YY("define_declare 2");
				DBG_YY("$2 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				yyval.declare_->is_def_ = 1;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 39:
	{
				DBG_YY("arg_list 1");
				yyval.arg_list_ = 0;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 40:
	{
				DBG_YY("arg_list 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].arg_list_));
				assert(yyvsp[0].arg_list_);
				yyval.arg_list_ = yyvsp[0].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 41:
	{
				DBG_YY("arg_list_not_empty 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[0].expr_);
				yyval.arg_list_ = New<CArgList>(LINE_NO);
				yyval.arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 42:
	{
				DBG_YY("arg_list_not_empty 2");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].arg_list_));
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].arg_list_ && yyvsp[0].expr_);
				yyval.arg_list_ = yyvsp[-2].arg_list_;
				yyval.arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 43:
	{
				DBG_YY("array_type 1");
				DBG_YY("$1 = "<<yyvsp[-2].token_);
				yyval.array_type_ = New<CArrayType>(LINE_NO);
				yyval.array_type_->tp_token_ = yyvsp[-2].token_;
				yyval.array_type_->has_sz_ = false;
				yyval.array_type_->sz_expr_ = 0;
				DBG_YY("$$ = "<<to_str(yyval.array_type_));
			}
break;
case 44:
	{
				DBG_YY("array_type 2");
				DBG_YY("$1 = "<<yyvsp[-3].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[-1].expr_));
				assert(yyvsp[-1].expr_);
				yyval.array_type_ = New<CArrayType>(LINE_NO);
				yyval.array_type_->tp_token_ = yyvsp[-3].token_;
				yyval.array_type_->has_sz_ = true;
				yyval.array_type_->sz_expr_ = yyvsp[-1].expr_;
				DBG_YY("$$ = "<<to_str(yyval.array_type_));
			}
break;
case 45:
	{
				DBG_YY("sim_type_name 1");
				DBG_YY("$1 = "<<yyvsp[-1].token_);
				DBG_YY("$2 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[0].var_);
				yyval.var_ = yyvsp[0].var_;
				if(yyval.var_->ref_count_ > 0){
					/*redefinition, but we need the whole declaration*/
					CSharedPtr<CVariable> t = yyval.var_;
					yyval.var_ = New<CVariable>(LINE_NO);
					yyval.var_->shadow_ = t;
					yyval.var_->varname_ = t->varname_;
					yyval.var_->host_cmd_ = CUR_CMD;
				}
				yyval.var_->tp_token_ = yyvsp[-1].token_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 46:
	{
				DBG_YY("expr 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].fix_value_));
				assert(yyvsp[0].fix_value_);
				yyval.expr_ = New<CExpr>(LINE_NO);
				yyval.expr_->type_ = 1;
				yyval.expr_->fix_value_ = yyvsp[0].fix_value_;
				DBG_YY("$$ = "<<to_str(yyval.expr_));
			}
break;
case 47:
	{
				DBG_YY("expr 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].func_call_));
				assert(yyvsp[0].func_call_);
				yyval.expr_ = New<CExpr>(LINE_NO);
				yyval.expr_->type_ = 2;
				yyval.expr_->func_call_ = yyvsp[0].func_call_;
				DBG_YY("$$ = "<<to_str(yyval.expr_));
			}
break;
case 48:
	{
				DBG_YY("expr 3");
				DBG_YY("$1 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[0].var_);
				yyval.expr_ = New<CExpr>(LINE_NO);
				yyval.expr_->type_ = 3;
				yyval.expr_->var_ = yyvsp[0].var_;
				DBG_YY("$$ = "<<to_str(yyval.expr_));
			}
break;
case 49:
	{
				DBG_YY("fix_value 1");
				DBG_YY("$1 = "<<yyvsp[0].int_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_INT;
				yyval.fix_value_->int_ = yyvsp[0].int_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 50:
	{
				DBG_YY("fix_value 2");
				DBG_YY("$1 = "<<yyvsp[0].long_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_LONG;
				yyval.fix_value_->long_ = yyvsp[0].long_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 51:
	{
				DBG_YY("fix_value 3");
				DBG_YY("$1 = "<<yyvsp[0].i64_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_I64;
				yyval.fix_value_->i64_ = yyvsp[0].i64_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 52:
	{
				DBG_YY("fix_value 4");
				DBG_YY("$1 = "<<yyvsp[0].strIdx_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_STR;
				yyval.fix_value_->strIdx_ = yyvsp[0].strIdx_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 53:
	{
				DBG_YY("fix_value 5");
				DBG_YY("$1 = "<<yyvsp[0].prog_arg_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_PA;
				yyval.fix_value_->prog_arg_ = yyvsp[0].prog_arg_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 54:
	{DBG_YY("func_name = FUN("<<FUN<<")");yyval.token_ = FUN;}
break;
case 55:
	{DBG_YY("func_name = BEGIN("<<BEGIN_<<")");yyval.token_ = BEGIN_;}
break;
case 56:
	{DBG_YY("func_name = END("<<END<<")");yyval.token_ = END;}
break;
case 57:
	{DBG_YY("func_name = HBO("<<HBO<<")");yyval.token_ = HBO;}
break;
case 58:
	{DBG_YY("func_name = NBO("<<NBO<<")");yyval.token_ = NBO;}
break;
case 59:
	{DBG_YY("func_name = SEND("<<SEND<<")");yyval.token_ = SEND;}
break;
case 60:
	{DBG_YY("func_name = RECV("<<RECV<<")");yyval.token_ = RECV;}
break;
case 61:
	{DBG_YY("func_name = HEX("<<HEX<<")");yyval.token_ = HEX;}
break;
case 62:
	{DBG_YY("func_name = UNHEX("<<UNHEX<<")");yyval.token_ = UNHEX;}
break;
case 63:
	{DBG_YY("func_name = PRINT("<<PRINT<<")");yyval.token_ = PRINT;}
break;
case 64:
	{DBG_YY("func_name = IP NBO("<<__IPN<<")");yyval.token_ = __IPN;}
break;
case 65:
	{DBG_YY("func_name = IP HBO("<<__IPH<<")");yyval.token_ = __IPH;}
break;
case 66:
	{DBG_YY("func_name = ARRAY("<<ARRAY<<")");yyval.token_ = ARRAY;}
break;
case 67:
	{DBG_YY("func_name = END ARRAY("<<__END_ARRAY<<")");yyval.token_ = __END_ARRAY;}
break;
case 68:
	{DBG_YY("func_name = SLEEP("<<SLEEP<<")");yyval.token_ = SLEEP;}
break;
case 69:
	{DBG_YY("simple_type = U8("<<TP_U8<<")");yyval.token_ = TP_U8;}
break;
case 70:
	{DBG_YY("simple_type = S8("<<TP_S8<<")");yyval.token_ = TP_S8;}
break;
case 71:
	{DBG_YY("simple_type = U16("<<TP_U16<<")");yyval.token_ =  TP_U16;}
break;
case 72:
	{DBG_YY("simple_type = S16("<<TP_S16<<")");yyval.token_ = TP_S16;}
break;
case 73:
	{DBG_YY("simple_type = U32("<<TP_U32<<")");yyval.token_ = TP_U32;}
break;
case 74:
	{DBG_YY("simple_type = S32("<<TP_S32<<")");yyval.token_ = TP_S32;}
break;
case 75:
	{DBG_YY("simple_type = U64("<<TP_U64<<")");yyval.token_ = TP_U64;}
break;
case 76:
	{DBG_YY("simple_type = S64("<<TP_S64<<")");yyval.token_ = TP_S64;}
break;
case 77:
	{DBG_YY("simple_type = STR("<<STR<<")");yyval.token_ = STR;}
break;
case 78:
	{DBG_YY("simple_type = RAW("<<RAW<<")");yyval.token_ =  RAW;}
break;
case 79:
	{DBG_YY("simple_type = TCP("<<TCP<<")");yyval.token_ = TCP;}
break;
case 80:
	{DBG_YY("simple_type = UDP("<<UDP<<")");yyval.token_ = UDP;}
break;
case 81:
	{DBG_YY("comp_op = OP_LG("<<OP_LG<<")");yyval.token_ = OP_LG;}
break;
case 82:
	{DBG_YY("comp_op = OP_SM("<<OP_SM<<")");yyval.token_ = OP_SM;}
break;
case 83:
	{DBG_YY("comp_op = OP_LEQ("<<OP_LEQ<<")");yyval.token_ = OP_LEQ;}
break;
case 84:
	{DBG_YY("comp_op = OP_SEQ("<<OP_SEQ<<")");yyval.token_ = OP_SEQ;}
break;
case 85:
	{DBG_YY("comp_op = OP_EQ("<<OP_EQ<<")");yyval.token_ = OP_EQ;}
break;
case 86:
	{DBG_YY("comp_op = OP_NEQ("<<OP_NEQ<<")");yyval.token_ = OP_NEQ;}
break;
case 87:
	{DBG_YY("comp_op = OP_NOT("<<OP_NOT<<")");yyval.token_ = OP_NOT;}
break;
case 88:
	{DBG_YY("stream_op = OP_IN("<<OP_IN<<")");yyval.token_ = OP_IN;}
break;
case 89:
	{DBG_YY("stream_op = OP_OUT("<<OP_OUT<<")");yyval.token_ = OP_OUT;}
break;
case 90:
	{DBG_YY("stmt_sep = ;");}
break;
case 91:
	{DBG_YY("stmt_sep = NL");}
break;
case 92:
	{DBG_YY("stmt_sep = EOF");}
break;
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = (short) yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
