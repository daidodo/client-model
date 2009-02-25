#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20050813

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

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
short yylhs[] = {                                        -1,
    0,    0,   15,   15,   16,   16,   16,   17,   19,   19,
   21,   21,   21,   20,   20,   22,   13,   13,   14,   14,
   14,   11,   11,   12,   12,   12,   12,   12,   12,   12,
   12,   12,    9,    9,   10,   10,    8,    8,    6,    7,
    7,    7,    5,    5,    5,    5,    5,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    3,    3,    3,    3,    3,
    3,    4,    4,   18,   18,   18,
};
short yylen[] = {                                         2,
    0,    2,    1,    1,    1,    2,    2,    4,    1,    2,
    1,    2,    2,    1,    2,    2,    1,    2,    1,    4,
    4,    3,    2,    2,    1,    3,    4,    3,    5,    3,
    3,    3,    0,    1,    1,    3,    3,    4,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    2,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      1,
    0,   85,   86,    0,    0,   63,   64,   65,   66,   67,
   68,   69,   70,   71,   72,   73,   74,   48,    0,    0,
   51,   52,   53,   54,   55,   56,   57,    0,   62,   84,
    0,    0,    0,    0,   17,    0,    9,    2,    3,    4,
    5,    0,    0,   15,    0,   18,   60,   61,   59,   58,
   39,    0,    0,    0,    0,   75,   76,   77,   78,   79,
   80,   81,   82,   83,    0,    0,    0,    0,    0,   24,
    7,    0,   10,    6,   11,    0,   43,   44,   45,   46,
   42,   47,   40,   35,    0,    0,   41,   37,    0,    0,
   28,    0,   26,    0,   30,    0,   31,    0,    0,    0,
   13,    0,   12,    0,   21,    0,   38,   20,   27,    0,
   16,   23,    0,    8,   36,   29,   22,
};
short yydgoto[] = {                                       1,
   72,   32,   68,   69,   83,   33,   84,   34,   85,   86,
  101,   35,   36,   87,   38,   39,   40,   41,   42,   43,
   76,  104,
};
short yysindex[] = {                                      0,
  283,    0,    0, -285, -160,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -266, -264,
    0,    0,    0,    0,    0,    0,    0, -251,    0,    0,
  -35,  -12,   82, -274,    0,  -56,    0,    0,    0,    0,
    0,  378,  312,    0,  -89,    0,    0,    0,    0,    0,
    0,  469,  426,  469,  469,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  469,  469,  -10,  469,  469,    0,
    0,   -7,    0,    0,    0,  186,    0,    0,    0,    0,
    0,    0,    0,    0,   -6,   -8,    0,    0,  -59,   -4,
    0,   -3,    0,  469,    0,   -7,    0, -246,  469, -167,
    0,    0,    0,  -56,    0,  469,    0,    0,    0,   -1,
    0,    0,  469,    0,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,  350,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -40,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   56,  -53,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1,    0,    1,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    1,    0,  -51,    0,  124,    0,    0,
    0,  234,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   11,    0,  -61,    0,    0,    0,  -44,    0,  -34,    0,
    0,   40,    0,   16,    0,  -33,    0,  -29,    0,    0,
    0,    0,
};
#define YYTABLESIZE 773
short yytable[] = {                                      49,
   49,   53,   30,   49,   52,   25,   71,   32,   89,   75,
   91,   31,   74,  111,   99,   45,   37,   44,   49,   90,
   47,   93,   48,   95,   97,   49,   50,   54,   70,   94,
   92,  100,   52,  107,  105,  106,  108,  109,  113,  116,
   48,   33,  103,   34,   46,    0,    0,   50,   50,    0,
    0,   50,   49,   31,  112,   53,    0,   73,   37,  110,
    0,  115,    0,    0,    0,    0,   50,    0,  117,    0,
    0,    0,    0,    0,  114,    0,    0,    0,    0,   96,
    0,    0,    0,    0,    0,    0,   31,    0,    0,    0,
    0,  102,    0,    0,    0,    0,   19,    0,    0,   19,
   50,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,    0,   19,    0,    0,    0,    0,    0,
    0,   65,   56,   57,   58,   59,   60,   61,   62,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   67,
    0,    0,   66,    0,    0,    0,    0,    0,   19,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   50,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   50,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    2,    3,    0,   25,   25,   32,   32,    0,    0,    0,
    0,    0,    0,   51,    0,    0,   49,   49,    0,    0,
   49,   49,   49,   49,   49,   49,   49,   49,   49,   49,
   49,   49,   49,   49,   49,   49,   49,   49,   49,   49,
   49,   49,   49,   49,   30,    0,    0,    0,   49,   49,
   49,   49,   49,   49,   49,   49,    0,    0,   49,   49,
   49,   49,   49,   49,   50,   50,    0,   51,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   50,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   50,   50,   50,
   50,   50,    9,    0,    0,    0,   50,   50,   50,   50,
   50,   50,   50,   50,    0,    0,   50,   50,   50,   50,
   50,   50,   19,   19,    0,    0,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   19,
   55,   30,    0,    0,   19,   19,   19,   19,   19,   19,
   19,   19,    0,    0,   19,   19,   19,   19,   19,   19,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   30,   56,   57,   58,   59,   60,   61,   62,   63,   64,
   50,   50,    0,    0,    0,   50,   50,   50,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   50,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   50,   14,    0,
    0,    0,   50,   50,   50,   50,   50,   50,   50,   50,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   30,    0,    0,    0,
    0,    0,    2,    3,    0,    0,    5,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   98,   21,   22,   23,   24,   25,   26,   27,   28,
    0,    0,    0,    0,   29,   56,   57,   58,   59,   60,
   61,   62,    0,    0,   77,   78,   79,   80,   81,   82,
    9,    9,    0,    0,    0,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,   88,    0,
    0,    0,    9,   41,   41,   41,   41,   41,   41,   41,
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
    0,    0,    0,    0,   77,   78,   79,   80,   81,   82,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
   26,   27,   28,    0,    0,    0,    0,   29,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   77,   78,   79,
   80,   81,   82,
};
short yycheck[] = {                                      40,
   41,   91,   59,   44,   40,   59,   36,   59,   53,   43,
   55,    1,   42,  260,   76,    5,    1,  303,   59,   54,
  287,   66,  287,   68,   69,  277,  278,   40,  303,   40,
   65,   76,   40,   93,   41,   44,   41,   41,  100,   41,
  287,   41,   76,   41,    5,   -1,   -1,   40,   41,   -1,
   -1,   44,   93,   43,   99,   91,   -1,   42,   43,   94,
   -1,  106,   -1,   -1,   -1,   -1,   59,   -1,  113,   -1,
   -1,   -1,   -1,   -1,  104,   -1,   -1,   -1,   -1,   69,
   -1,   -1,   -1,   -1,   -1,   -1,   76,   -1,   -1,   -1,
   -1,   76,   -1,   -1,   -1,   -1,   41,   -1,   -1,   44,
   93,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,   -1,   59,   -1,   -1,   -1,   -1,   -1,
   -1,   40,  290,  291,  292,  293,  294,  295,  296,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,
   -1,   -1,   61,   -1,   -1,   -1,   -1,   -1,   93,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   40,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,   -1,  257,  258,  257,  258,   -1,   -1,   -1,
   -1,   -1,   -1,  303,   -1,   -1,  257,  258,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,   59,   -1,   -1,   -1,  289,  290,
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
char *yyname[] = {
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
char *yyrule[] = {
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
"declare : simple_declare",
"declare : DEF simple_declare",
"func_call : func_name",
"func_call : func_name '(' arg_list ')'",
"func_call : simple_type '(' arg_list ')'",
"assert_exp : expr comp_op expr",
"assert_exp : comp_op expr",
"simple_declare : array_type VAR_NAME",
"simple_declare : sim_type_name",
"simple_declare : sim_type_name '=' expr",
"simple_declare : sim_type_name '(' arg_list ')'",
"simple_declare : sim_type_name IEQ expr",
"simple_declare : sim_type_name ':' '(' arg_list ')'",
"simple_declare : sim_type_name comp_op expr",
"simple_declare : sim_type_name stream_op expr",
"simple_declare : sim_type_name stream_op simple_type",
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
static int      yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
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

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

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

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

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
        *++yyssp = yystate = yytable[yyn];
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
                *++yyssp = yystate = yytable[yyn];
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
    yyval = yyvsp[1-yym];
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
				DBG_YY("$2 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				yyval.declare_->is_def_ = 1;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 19:
{
				DBG_YY("func_call 1");
				DBG_YY("$1 = "<<yyvsp[0].token_);
				yyval.func_call_ = New<CFuncCall>(LINE_NO);
				yyval.func_call_->ft_token_ = yyvsp[0].token_;
				DBG_YY("$$ = "<<to_str(yyval.func_call_));
			}
break;
case 20:
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
case 21:
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
case 22:
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
case 23:
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
case 24:
{
				DBG_YY("simple_declare 1");
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
				yyval.declare_->var_->type_ = 2;
				yyval.declare_->var_->array_type_ = yyvsp[-1].array_type_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 25:
{
				DBG_YY("simple_declare 2");
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
case 26:
{
				DBG_YY("simple_declare 3");
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
case 27:
{
				DBG_YY("simple_declare 4");
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
case 28:
{
				DBG_YY("simple_declare 5");
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
case 29:
{
				DBG_YY("simple_declare 6");
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
case 30:
{
				DBG_YY("simple_declare 7");
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
case 31:
{
				DBG_YY("simple_declare 8");
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
case 32:
{
				DBG_YY("simple_declare 9");
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
case 33:
{
				DBG_YY("arg_list 1");
				yyval.arg_list_ = 0;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 34:
{
				DBG_YY("arg_list 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].arg_list_));
				assert(yyvsp[0].arg_list_);
				yyval.arg_list_ = yyvsp[0].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 35:
{
				DBG_YY("arg_list_not_empty 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[0].expr_);
				yyval.arg_list_ = New<CArgList>(LINE_NO);
				yyval.arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 36:
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
case 37:
{
				DBG_YY("array_type 1");
				DBG_YY("$1 = "<<yyvsp[-2].token_);
				yyval.array_type_ = New<CArrayType>(LINE_NO);
				yyval.array_type_->tp_token_ = yyvsp[-2].token_;
				yyval.array_type_->expr_ = 0;
				DBG_YY("$$ = "<<to_str(yyval.array_type_));
			}
break;
case 38:
{
				DBG_YY("array_type 2");
				DBG_YY("$1 = "<<yyvsp[-3].token_);
				DBG_YY("$3 = "<<to_str(yyvsp[-1].expr_));
				assert(yyvsp[-1].expr_);
				yyval.array_type_ = New<CArrayType>(LINE_NO);
				yyval.array_type_->tp_token_ = yyvsp[-3].token_;
				yyval.array_type_->expr_ = yyvsp[-1].expr_;
				DBG_YY("$$ = "<<to_str(yyval.array_type_));
			}
break;
case 39:
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
				yyval.var_->type_ = 1;
				yyval.var_->tp_token_ = yyvsp[-1].token_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 40:
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
case 41:
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
case 42:
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
case 43:
{
				DBG_YY("fix_value 1");
				DBG_YY("$1 = "<<yyvsp[0].int_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_INT;
				yyval.fix_value_->int_ = yyvsp[0].int_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 44:
{
				DBG_YY("fix_value 2");
				DBG_YY("$1 = "<<yyvsp[0].long_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_LONG;
				yyval.fix_value_->long_ = yyvsp[0].long_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 45:
{
				DBG_YY("fix_value 3");
				DBG_YY("$1 = "<<yyvsp[0].i64_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_I64;
				yyval.fix_value_->i64_ = yyvsp[0].i64_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 46:
{
				DBG_YY("fix_value 4");
				DBG_YY("$1 = "<<yyvsp[0].strIdx_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_STR;
				yyval.fix_value_->strIdx_ = yyvsp[0].strIdx_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 47:
{
				DBG_YY("fix_value 5");
				DBG_YY("$1 = "<<yyvsp[0].prog_arg_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_PA;
				yyval.fix_value_->prog_arg_ = yyvsp[0].prog_arg_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 48:
{DBG_YY("func_name = FUN("<<FUN<<")");yyval.token_ = FUN;}
break;
case 49:
{DBG_YY("func_name = BEGIN("<<BEGIN_<<")");yyval.token_ = BEGIN_;}
break;
case 50:
{DBG_YY("func_name = END("<<END<<")");yyval.token_ = END;}
break;
case 51:
{DBG_YY("func_name = HBO("<<HBO<<")");yyval.token_ = HBO;}
break;
case 52:
{DBG_YY("func_name = NBO("<<NBO<<")");yyval.token_ = NBO;}
break;
case 53:
{DBG_YY("func_name = SEND("<<SEND<<")");yyval.token_ = SEND;}
break;
case 54:
{DBG_YY("func_name = RECV("<<RECV<<")");yyval.token_ = RECV;}
break;
case 55:
{DBG_YY("func_name = HEX("<<HEX<<")");yyval.token_ = HEX;}
break;
case 56:
{DBG_YY("func_name = UNHEX("<<UNHEX<<")");yyval.token_ = UNHEX;}
break;
case 57:
{DBG_YY("func_name = PRINT("<<PRINT<<")");yyval.token_ = PRINT;}
break;
case 58:
{DBG_YY("func_name = IP NBO("<<__IPN<<")");yyval.token_ = __IPN;}
break;
case 59:
{DBG_YY("func_name = IP HBO("<<__IPH<<")");yyval.token_ = __IPH;}
break;
case 60:
{DBG_YY("func_name = ARRAY("<<ARRAY<<")");yyval.token_ = ARRAY;}
break;
case 61:
{DBG_YY("func_name = END ARRAY("<<__END_ARRAY<<")");yyval.token_ = __END_ARRAY;}
break;
case 62:
{DBG_YY("func_name = SLEEP("<<SLEEP<<")");yyval.token_ = SLEEP;}
break;
case 63:
{DBG_YY("simple_type = U8("<<TP_U8<<")");yyval.token_ = TP_U8;}
break;
case 64:
{DBG_YY("simple_type = S8("<<TP_S8<<")");yyval.token_ = TP_S8;}
break;
case 65:
{DBG_YY("simple_type = U16("<<TP_U16<<")");yyval.token_ =  TP_U16;}
break;
case 66:
{DBG_YY("simple_type = S16("<<TP_S16<<")");yyval.token_ = TP_S16;}
break;
case 67:
{DBG_YY("simple_type = U32("<<TP_U32<<")");yyval.token_ = TP_U32;}
break;
case 68:
{DBG_YY("simple_type = S32("<<TP_S32<<")");yyval.token_ = TP_S32;}
break;
case 69:
{DBG_YY("simple_type = U64("<<TP_U64<<")");yyval.token_ = TP_U64;}
break;
case 70:
{DBG_YY("simple_type = S64("<<TP_S64<<")");yyval.token_ = TP_S64;}
break;
case 71:
{DBG_YY("simple_type = STR("<<STR<<")");yyval.token_ = STR;}
break;
case 72:
{DBG_YY("simple_type = RAW("<<RAW<<")");yyval.token_ =  RAW;}
break;
case 73:
{DBG_YY("simple_type = TCP("<<TCP<<")");yyval.token_ = TCP;}
break;
case 74:
{DBG_YY("simple_type = UDP("<<UDP<<")");yyval.token_ = UDP;}
break;
case 75:
{DBG_YY("comp_op = OP_LG("<<OP_LG<<")");yyval.token_ = OP_LG;}
break;
case 76:
{DBG_YY("comp_op = OP_SM("<<OP_SM<<")");yyval.token_ = OP_SM;}
break;
case 77:
{DBG_YY("comp_op = OP_LEQ("<<OP_LEQ<<")");yyval.token_ = OP_LEQ;}
break;
case 78:
{DBG_YY("comp_op = OP_SEQ("<<OP_SEQ<<")");yyval.token_ = OP_SEQ;}
break;
case 79:
{DBG_YY("comp_op = OP_EQ("<<OP_EQ<<")");yyval.token_ = OP_EQ;}
break;
case 80:
{DBG_YY("comp_op = OP_NEQ("<<OP_NEQ<<")");yyval.token_ = OP_NEQ;}
break;
case 81:
{DBG_YY("comp_op = OP_NOT("<<OP_NOT<<")");yyval.token_ = OP_NOT;}
break;
case 82:
{DBG_YY("stream_op = OP_IN("<<OP_IN<<")");yyval.token_ = OP_IN;}
break;
case 83:
{DBG_YY("stream_op = OP_OUT("<<OP_OUT<<")");yyval.token_ = OP_OUT;}
break;
case 84:
{DBG_YY("stmt_sep = ;");}
break;
case 85:
{DBG_YY("stmt_sep = NL");}
break;
case 86:
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
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
