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
#define STR1 271
#define STR2 272
#define STR4 273
#define RAW 274
#define TCP 275
#define UDP 276
#define FUN 277
#define BEGIN_ 278
#define END 279
#define HBO 280
#define NBO 281
#define SEND 282
#define RECV 283
#define HEX 284
#define UNHEX 285
#define PRINT 286
#define IP 287
#define __IPN 288
#define __IPH 289
#define ARRAY 290
#define __END_ARRAY 291
#define SLEEP 292
#define __DEBUG 293
#define OP_LG 294
#define OP_SM 295
#define OP_LEQ 296
#define OP_SEQ 297
#define OP_EQ 298
#define OP_NEQ 299
#define OP_NOT 300
#define OP_IN 301
#define OP_OUT 302
#define INT 303
#define LONG 304
#define I64 305
#define QSTRING 306
#define PROG_ARG 307
#define VAR_NAME 308
#define VAR_REF 309
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   22,   22,   23,   23,   23,   24,   26,   26,
   14,   14,   14,   14,   14,   14,   28,   28,   28,   27,
   27,   29,   21,   21,   21,   15,   15,   16,   16,   16,
   17,   17,   17,   17,   17,   18,   19,   19,   20,   20,
   13,   13,   11,   11,   12,   12,    8,    8,    8,    7,
    9,    9,    9,   10,   10,    6,    6,    5,    5,    5,
    5,    5,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    4,    4,   25,   25,   25,
};
static const short yylen[] = {                            2,
    0,    2,    1,    1,    1,    2,    2,    4,    1,    2,
    1,    1,    1,    1,    1,    1,    1,    2,    2,    1,
    2,    2,    1,    4,    4,    3,    5,    1,    3,    4,
    1,    5,    3,    5,    3,    3,    3,    3,    2,    2,
    3,    2,    0,    1,    1,    3,    2,    4,    5,    2,
    1,    1,    1,    3,    4,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    2,    2,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const short yydefred[] = {                         1,
    0,  104,  105,    0,    0,   79,   80,   81,   82,   83,
   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,
   63,    0,    0,   66,   67,   68,   69,   70,   71,   72,
    0,   77,   78,  103,    0,    0,    0,    0,    0,    0,
   11,   12,   13,   14,   15,   16,    9,    2,    3,    4,
    5,    0,    0,   21,    0,    0,   39,   40,   75,   76,
   74,   73,    0,    0,    0,    0,    0,   94,   95,   96,
   97,   98,   99,  100,  101,  102,    0,    0,    0,    0,
    0,    0,    0,   47,    7,    0,   10,    6,   17,    0,
   50,    0,   58,   59,   60,   61,   62,   56,   57,   51,
   53,   45,    0,    0,   52,   54,    0,    0,   26,    0,
    0,   29,   36,    0,   37,    0,   33,    0,   35,    0,
    0,    0,   19,    0,   18,    0,   48,    0,   25,    0,
   55,   24,   30,    0,    0,    0,   22,   42,    0,    8,
   49,   46,   27,   32,   34,   41,
};
static const short yydgoto[] = {                          1,
   86,   36,   80,   81,  100,  101,   37,   38,  102,   39,
  103,  104,  123,   40,   41,   42,   43,   44,   45,   46,
  105,   48,   49,   50,   51,   52,   53,   90,  126,
};
static const short yysindex[] = {                         0,
  310,    0,    0, -291,  -91,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -267, -264,    0,    0,    0,    0,    0,    0,    0,
 -250,    0,    0,    0,  -35,  -12,  109,  -48, -271,  -57,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  431,  343,    0, -269,  -11,    0,    0,    0,    0,
    0,    0,  -50,  699,  464,  699,  699,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  699,    2,  699,  699,
  699,  596,  651,    0,    0,    4,    0,    0,    0,  202,
    0,  538,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -1,    5,    0,    0,  -41,   16,    0,   29,
  699,    0,    0,    4,    0,  699,    0,  699,    0, -239,
  699, -231,    0,    0,    0,  -57,    0,  -22,    0,  699,
    0,    0,    0,   34,  -32,  -30,    0,    0,  699,    0,
    0,    0,    0,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,  384,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -40,   14,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   67,  -53,  -51,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -53,    0,    0,    0,    0,
    0,    0,   98,   35,    0,   35,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   35,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   36,    0,    0,    0,    0,    0,    0,
   35,    0,    0,  -49,    0,    0,    0,    0,    0,  155,
    0,    0,    0,  256,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    6,    0,  -74,    0,    0,    0,   41,    0,  -47,    0,
  -39,  -94,    0,    0,   73,   74,    0,    0,    0,    0,
    8,    0,  -28,    0,  -37,    0,    0,    0,    0,
};
#define YYTABLESIZE 1008
static const short yytable[] = {                         64,
   64,   34,   85,   64,   64,   28,   35,   31,   47,   38,
   55,  130,   83,  130,   88,  121,   54,  107,   64,  109,
  137,  135,   59,  136,   89,   60,  108,   66,   77,   61,
   62,  112,  113,  115,  117,  119,   84,  110,   91,  129,
   92,  111,  122,   64,  128,   56,   78,  139,  130,   79,
   60,  131,   64,   65,   65,   65,  132,   65,   35,   87,
   47,  125,   68,   69,   70,   71,   72,   73,   74,  133,
  141,  134,   65,  138,  143,   43,   44,   57,   58,    0,
    0,    0,  142,    0,   64,    0,  114,    0,  140,    0,
    0,  146,  144,    0,  145,   35,    0,  124,    0,    0,
    0,    0,    0,    0,    0,    0,   65,   23,    0,    0,
   23,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   23,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   50,   65,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   77,    0,
    0,    0,    0,    0,    0,   50,   50,    0,   50,   23,
    0,    0,    0,    0,    0,    0,   78,    0,    0,   79,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,    0,    0,    0,    0,    0,
    0,   23,    0,    0,   65,    0,    0,    0,    0,    2,
    3,    0,    0,   28,   28,   31,   31,   38,   38,    0,
   82,    0,    0,   65,    0,    0,   64,   64,    0,    0,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   64,   64,   64,   67,    0,    0,
    0,   64,   64,   64,   64,   64,   64,   64,   64,   64,
   34,    0,   64,   64,   64,   64,   64,   64,   64,    0,
   65,   65,   63,    0,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   65,    0,    0,    0,    0,   65,   65,   65,   65,   65,
   65,   65,   65,   65,    9,    0,   65,   65,   65,   65,
   65,   65,   65,   23,   23,    0,    0,   23,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
   23,   23,   23,   23,   50,   50,   50,    0,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   67,   34,   23,
   23,   23,   23,   23,   23,   23,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   50,   50,   50,   50,   50,   50,   50,   50,   50,
    0,   34,   68,   69,   70,   71,   72,   73,   74,   75,
   76,   65,   65,    0,    0,    0,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   65,   65,   20,    0,    0,    0,   65,   65,   65,   65,
   65,   65,   65,   65,   65,    0,    0,    0,    2,    3,
    0,    0,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
  120,   24,   25,   26,   27,   28,   29,   30,   31,   34,
    0,    0,    0,   32,   33,   68,   69,   70,   71,   72,
   73,   74,    0,    0,   93,   94,   95,   96,   97,   98,
   99,    0,    9,    9,    0,    0,    0,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    0,    0,    0,    0,    9,    9,   52,
   52,   52,   52,   52,   52,   52,  106,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    2,    3,    0,    4,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,   30,   31,    0,    0,    2,
    3,   32,   33,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
  127,    0,    0,    0,   32,   33,    0,    0,    0,    0,
   20,   20,    0,    0,   20,   20,   20,   20,   20,   20,
   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,
   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,
   20,    0,    0,    0,    0,   20,   20,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    2,    3,    0,
    0,    0,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,  116,    0,
    0,    0,   32,   33,    0,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
   31,    0,    0,    0,    0,   32,   33,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   93,   94,   95,   96,
   97,   98,   99,  118,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,   30,   31,    0,    0,    0,    0,   32,
   33,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   93,   94,   95,   96,   97,   98,   99,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
   29,   30,   31,    0,    0,    0,    0,   32,   33,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   93,   94,
   95,   96,   97,   98,   99,    0,    0,    0,    0,    0,
    0,    0,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,    0,    0,
    0,    0,   32,   33,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   93,   94,   95,   96,   97,   98,   99,
    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
   26,   27,   28,   29,   30,   31,    0,    0,    0,    0,
   32,   33,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   93,   94,   95,   96,   97,   98,   99,
};
static const short yycheck[] = {                         40,
   41,   59,   40,   44,   40,   59,    1,   59,    1,   59,
    5,   44,   61,   44,   52,   90,  308,   65,   59,   67,
  260,  116,  290,  118,   53,  290,   66,   40,   40,  280,
  281,   79,   80,   81,   82,   83,  308,   77,  308,   41,
   91,   40,   90,   40,   92,    5,   58,  122,   44,   61,
  290,   93,   93,   40,   41,   91,   41,   44,   53,   52,
   53,   90,  294,  295,  296,  297,  298,  299,  300,   41,
   93,  111,   59,  121,   41,   41,   41,    5,    5,   -1,
   -1,   -1,  130,   -1,  125,   -1,   81,   -1,  126,   -1,
   -1,  139,  125,   -1,  125,   90,   -1,   90,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   41,   -1,   -1,
   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   40,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,   -1,   61,   93,
   -1,   -1,   -1,   -1,   -1,   -1,   58,   -1,   -1,   61,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,  125,   -1,   -1,   40,   -1,   -1,   -1,   -1,  257,
  258,   -1,   -1,  257,  258,  257,  258,  257,  258,   -1,
  259,   -1,   -1,   59,   -1,   -1,  257,  258,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  259,   -1,   -1,
   -1,  292,  293,  294,  295,  296,  297,  298,  299,  300,
   59,   -1,  303,  304,  305,  306,  307,  308,  309,   -1,
  257,  258,  308,   -1,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,   -1,   -1,   -1,   -1,  292,  293,  294,  295,  296,
  297,  298,  299,  300,   59,   -1,  303,  304,  305,  306,
  307,  308,  309,  257,  258,   -1,   -1,  261,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  286,  287,  257,  258,  259,   -1,  292,  293,
  294,  295,  296,  297,  298,  299,  300,  259,   59,  303,
  304,  305,  306,  307,  308,  309,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  294,  295,  296,  297,  298,  299,  300,  301,  302,
   -1,   59,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  257,  258,   -1,   -1,   -1,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
  286,  287,   59,   -1,   -1,   -1,  292,  293,  294,  295,
  296,  297,  298,  299,  300,   -1,   -1,   -1,  257,  258,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,  283,  284,  285,  286,  287,   59,
   -1,   -1,   -1,  292,  293,  294,  295,  296,  297,  298,
  299,  300,   -1,   -1,  303,  304,  305,  306,  307,  308,
  309,   -1,  257,  258,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,   -1,   -1,   -1,   -1,  292,  293,  294,
  295,  296,  297,  298,  299,  300,   93,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,   -1,   -1,  257,
  258,  292,  293,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  286,  287,
   93,   -1,   -1,   -1,  292,  293,   -1,   -1,   -1,   -1,
  257,  258,   -1,   -1,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,   -1,   -1,   -1,   -1,  292,  293,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  123,   -1,
   -1,   -1,  292,  293,   -1,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,   -1,   -1,   -1,   -1,  292,  293,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  303,  304,  305,  306,
  307,  308,  309,  123,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,  285,  286,  287,   -1,   -1,   -1,   -1,  292,
  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  303,  304,  305,  306,  307,  308,  309,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,   -1,   -1,   -1,   -1,  292,  293,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  303,  304,
  305,  306,  307,  308,  309,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,   -1,   -1,
   -1,   -1,  292,  293,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  303,  304,  305,  306,  307,  308,  309,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  286,  287,   -1,   -1,   -1,   -1,
  292,  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  303,  304,  305,  306,  307,  308,  309,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 309
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"NL","EOF_","IEQ","CMD","DEF","TP_U8","TP_S8","TP_U16","TP_S16","TP_U32",
"TP_S32","TP_U64","TP_S64","STR","STR1","STR2","STR4","RAW","TCP","UDP","FUN",
"BEGIN_","END","HBO","NBO","SEND","RECV","HEX","UNHEX","PRINT","IP","__IPN",
"__IPH","ARRAY","__END_ARRAY","SLEEP","__DEBUG","OP_LG","OP_SM","OP_LEQ",
"OP_SEQ","OP_EQ","OP_NEQ","OP_NOT","OP_IN","OP_OUT","INT","LONG","I64",
"QSTRING","PROG_ARG","VAR_NAME","VAR_REF",
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
"declare : constant_declare",
"declare : post_declare",
"declare : array_declare",
"declare : assert_declare",
"declare : stream_declare",
"declare : define_declare",
"stmt_assert_list : stmt",
"stmt_assert_list : stmt_assert_list stmt",
"stmt_assert_list : stmt_assert_list assert_exp",
"cmd_begin : CMD",
"cmd_begin : CMD VAR_NAME",
"cmd_end : END CMD",
"func_call : func_name",
"func_call : func_name '(' arg_list ')'",
"func_call : simple_type '(' arg_list ')'",
"constant_declare : sim_type_name IEQ expr",
"constant_declare : sim_type_name ':' '(' arg_list ')'",
"post_declare : sim_type_name",
"post_declare : sim_type_name '=' expr",
"post_declare : sim_type_name '(' arg_list ')'",
"array_declare : array_type_name",
"array_declare : array_type_name IEQ '{' arg_list_not_empty '}'",
"array_declare : array_type_name IEQ expr",
"array_declare : array_type_name '=' '{' arg_list_not_empty '}'",
"array_declare : array_type_name '=' expr",
"assert_declare : sim_type_name comp_op expr",
"stream_declare : sim_type_name stream_op expr",
"stream_declare : sim_type_name stream_op simple_type",
"define_declare : DEF constant_declare",
"define_declare : DEF post_declare",
"assert_exp : expr comp_op expr",
"assert_exp : comp_op expr",
"arg_list :",
"arg_list : arg_list_not_empty",
"arg_list_not_empty : expr",
"arg_list_not_empty : arg_list_not_empty ',' expr",
"array_type_name : array_type VAR_NAME",
"array_type_name : simple_type VAR_NAME '[' ']'",
"array_type_name : simple_type VAR_NAME '[' expr ']'",
"sim_type_name : simple_type VAR_NAME",
"expr : fix_value",
"expr : func_call",
"expr : variable",
"array_type : simple_type '[' ']'",
"array_type : simple_type '[' expr ']'",
"variable : VAR_NAME",
"variable : VAR_REF",
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
"func_name : __DEBUG",
"simple_type : TP_U8",
"simple_type : TP_S8",
"simple_type : TP_U16",
"simple_type : TP_S16",
"simple_type : TP_U32",
"simple_type : TP_S32",
"simple_type : TP_U64",
"simple_type : TP_S64",
"simple_type : STR",
"simple_type : STR1",
"simple_type : STR2",
"simple_type : STR4",
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
	{
				DBG_YY("declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 12:
	{
				DBG_YY("declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 13:
	{
				DBG_YY("declare 3");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 14:
	{
				DBG_YY("declare 4");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 15:
	{
				DBG_YY("declare 5");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 16:
	{
				DBG_YY("declare 6");
				DBG_YY("$1 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
				program().AddStmt(yyval.declare_);
			}
break;
case 17:
	{DBG_YY("stmt_list 1");}
break;
case 18:
	{DBG_YY("stmt_list 2");}
break;
case 19:
	{DBG_YY("stmt_list 3");}
break;
case 20:
	{DBG_YY("cmd_begin 1");program().CmdBegin(0);}
break;
case 21:
	{DBG_YY("cmd_begin 2");program().CmdBegin(yyvsp[0].var_);}
break;
case 22:
	{
				DBG_YY("cmd_end");
				assert(CUR_CMD);
				CUR_CMD->endlineno_ = LINE_NO;
				program().CmdEnd();
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
case 27:
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
case 28:
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
case 29:
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
case 30:
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
case 31:
	{
				DBG_YY("array_declare 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[0].var_);
				yyval.declare_ = New<CDeclare>(yyvsp[0].var_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[0].var_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 32:
	{
				DBG_YY("array_declare 2");
				DBG_YY("$1 = "<<to_str(yyvsp[-4].var_));
				DBG_YY("$4 = "<<to_str(yyvsp[-1].arg_list_));
				assert(yyvsp[-4].var_ && yyvsp[-1].arg_list_);
				yyval.declare_ = New<CDeclare>(yyvsp[-4].var_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[-4].var_;
				yyval.declare_->arglist_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 33:
	{
				DBG_YY("array_declare 3");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->expr_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 34:
	{
				DBG_YY("array_declare 4");
				DBG_YY("$1 = "<<to_str(yyvsp[-4].var_));
				DBG_YY("$4 = "<<to_str(yyvsp[-1].arg_list_));
				assert(yyvsp[-4].var_ && yyvsp[-1].arg_list_);
				yyval.declare_ = New<CDeclare>(yyvsp[-4].var_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[-4].var_;
				yyval.declare_->arglist_ = yyvsp[-1].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 35:
	{
				DBG_YY("array_declare 5");
				DBG_YY("$1 = "<<to_str(yyvsp[-2].var_));
				DBG_YY("$3 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[-2].var_ && yyvsp[0].expr_);
				yyval.declare_ = New<CDeclare>(yyvsp[-2].var_->lineno_);
				yyval.declare_->type_ = 1;
				yyval.declare_->var_ = yyvsp[-2].var_;
				yyval.declare_->expr_ = yyvsp[0].expr_;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 36:
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
case 37:
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
case 38:
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
case 39:
	{
				DBG_YY("define_declare 1");
				DBG_YY("$2 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				yyval.declare_->is_def_ = 1;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 40:
	{
				DBG_YY("define_declare 2");
				DBG_YY("$2 = "<<to_str(yyvsp[0].declare_));
				assert(yyvsp[0].declare_);
				yyval.declare_ = yyvsp[0].declare_;
				yyval.declare_->is_def_ = 1;
				DBG_YY("$$ = "<<to_str(yyval.declare_));
			}
break;
case 41:
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
case 42:
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
case 43:
	{
				DBG_YY("arg_list 1");
				yyval.arg_list_ = 0;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 44:
	{
				DBG_YY("arg_list 2");
				DBG_YY("$1 = "<<to_str(yyvsp[0].arg_list_));
				assert(yyvsp[0].arg_list_);
				yyval.arg_list_ = yyvsp[0].arg_list_;
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 45:
	{
				DBG_YY("arg_list_not_empty 1");
				DBG_YY("$1 = "<<to_str(yyvsp[0].expr_));
				assert(yyvsp[0].expr_);
				yyval.arg_list_ = New<CArgList>(LINE_NO);
				yyval.arg_list_->Add(yyvsp[0].expr_);
				DBG_YY("$$ = "<<to_str(yyval.arg_list_));
			}
break;
case 46:
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
case 47:
	{
				DBG_YY("array_type_name 1");
				DBG_YY("$1 = "<<to_str(yyvsp[-1].array_type_));
				DBG_YY("$2 = "<<to_str(yyvsp[0].var_));
				assert(yyvsp[-1].array_type_ && yyvsp[0].var_);
				yyval.var_ = yyvsp[0].var_;
				if(yyval.var_->ref_count_ > 0){
					/*redefinition, but we need the whole declaration*/
					CSharedPtr<CVariable> t = yyval.var_;
					yyval.var_ = New<CVariable>(LINE_NO);
					yyval.var_->shadow_ = t;
					yyval.var_->varname_ = t->varname_;
					yyval.var_->host_cmd_ = CUR_CMD;
				}
				yyval.var_->array_type_ = yyvsp[-1].array_type_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 48:
	{
				DBG_YY("array_type_name 2");
				DBG_YY("$2 = "<<to_str(yyvsp[-2].var_));
				assert(yyvsp[-2].var_);
				yyval.var_ = yyvsp[-2].var_;
				if(yyval.var_->ref_count_ > 0){
					/*redefinition, but we need the whole declaration*/
					CSharedPtr<CVariable> t = yyval.var_;
					yyval.var_ = New<CVariable>(LINE_NO);
					yyval.var_->shadow_ = t;
					yyval.var_->varname_ = t->varname_;
					yyval.var_->host_cmd_ = CUR_CMD;
				}
				yyval.var_->array_type_ = New<CArrayType>(LINE_NO);
				yyval.var_->array_type_->tp_token_ = yyvsp[-3].token_;
				yyval.var_->array_type_->has_sz_ = false;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 49:
	{
				DBG_YY("array_type_name 3");
				DBG_YY("$2 = "<<to_str(yyvsp[-3].var_));
				DBG_YY("$4 = "<<to_str(yyvsp[-1].expr_));
				assert(yyvsp[-3].var_ && yyvsp[-1].expr_);
				yyval.var_ = yyvsp[-3].var_;
				if(yyval.var_->ref_count_ > 0){
					/*redefinition, but we need the whole declaration*/
					CSharedPtr<CVariable> t = yyval.var_;
					yyval.var_ = New<CVariable>(LINE_NO);
					yyval.var_->shadow_ = t;
					yyval.var_->varname_ = t->varname_;
					yyval.var_->host_cmd_ = CUR_CMD;
				}
				yyval.var_->array_type_ = New<CArrayType>(LINE_NO);
				yyval.var_->array_type_->tp_token_ = yyvsp[-4].token_;
				yyval.var_->array_type_->has_sz_ = true;
				yyval.var_->array_type_->sz_expr_ = yyvsp[-1].expr_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 50:
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
case 51:
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
case 52:
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
case 53:
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
case 54:
	{
				DBG_YY("array_type 1");
				DBG_YY("$1 = "<<yyvsp[-2].token_);
				yyval.array_type_ = New<CArrayType>(LINE_NO);
				yyval.array_type_->tp_token_ = yyvsp[-2].token_;
				yyval.array_type_->has_sz_ = false;
				DBG_YY("$$ = "<<to_str(yyval.array_type_));
			}
break;
case 55:
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
case 56:
	{	DBG_YY("variable 1");
				DBG_YY("$1 = "<<yyvsp[0].var_);
				yyval.var_ = yyvsp[0].var_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 57:
	{	DBG_YY("variable 2");
				DBG_YY("$1 = "<<yyvsp[0].var_);
				yyval.var_ = yyvsp[0].var_;
				DBG_YY("$$ = "<<to_str(yyval.var_));
			}
break;
case 58:
	{
				DBG_YY("fix_value 1");
				DBG_YY("$1 = "<<yyvsp[0].int_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_INT;
				yyval.fix_value_->int_ = yyvsp[0].int_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 59:
	{
				DBG_YY("fix_value 2");
				DBG_YY("$1 = "<<yyvsp[0].long_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_LONG;
				yyval.fix_value_->long_ = yyvsp[0].long_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 60:
	{
				DBG_YY("fix_value 3");
				DBG_YY("$1 = "<<yyvsp[0].i64_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_I64;
				yyval.fix_value_->i64_ = yyvsp[0].i64_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 61:
	{
				DBG_YY("fix_value 4");
				DBG_YY("$1 = "<<yyvsp[0].strIdx_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_STR;
				yyval.fix_value_->strIdx_ = yyvsp[0].strIdx_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 62:
	{
				DBG_YY("fix_value 5");
				DBG_YY("$1 = "<<yyvsp[0].prog_arg_);
				yyval.fix_value_ = New<CFixValue>(LINE_NO);
				yyval.fix_value_->type_ = DT_PA;
				yyval.fix_value_->prog_arg_ = yyvsp[0].prog_arg_;
				DBG_YY("$$ = "<<to_str(yyval.fix_value_));
			}
break;
case 63:
	{DBG_YY("func_name = FUN("<<FUN<<")");yyval.token_ = FUN;}
break;
case 64:
	{DBG_YY("func_name = BEGIN("<<BEGIN_<<")");yyval.token_ = BEGIN_;}
break;
case 65:
	{DBG_YY("func_name = END("<<END<<")");yyval.token_ = END;}
break;
case 66:
	{DBG_YY("func_name = HBO("<<HBO<<")");yyval.token_ = HBO;}
break;
case 67:
	{DBG_YY("func_name = NBO("<<NBO<<")");yyval.token_ = NBO;}
break;
case 68:
	{DBG_YY("func_name = SEND("<<SEND<<")");yyval.token_ = SEND;}
break;
case 69:
	{DBG_YY("func_name = RECV("<<RECV<<")");yyval.token_ = RECV;}
break;
case 70:
	{DBG_YY("func_name = HEX("<<HEX<<")");yyval.token_ = HEX;}
break;
case 71:
	{DBG_YY("func_name = UNHEX("<<UNHEX<<")");yyval.token_ = UNHEX;}
break;
case 72:
	{DBG_YY("func_name = PRINT("<<PRINT<<")");yyval.token_ = PRINT;}
break;
case 73:
	{DBG_YY("func_name = IP NBO("<<__IPN<<")");yyval.token_ = __IPN;}
break;
case 74:
	{DBG_YY("func_name = IP HBO("<<__IPH<<")");yyval.token_ = __IPH;}
break;
case 75:
	{DBG_YY("func_name = ARRAY("<<ARRAY<<")");yyval.token_ = ARRAY;}
break;
case 76:
	{DBG_YY("func_name = END ARRAY("<<__END_ARRAY<<")");yyval.token_ = __END_ARRAY;}
break;
case 77:
	{DBG_YY("func_name = SLEEP("<<SLEEP<<")");yyval.token_ = SLEEP;}
break;
case 78:
	{DBG_YY("func_name = DEBUG("<<__DEBUG<<")");yyval.token_ = __DEBUG;}
break;
case 79:
	{DBG_YY("simple_type = U8("<<TP_U8<<")");yyval.token_ = TP_U8;}
break;
case 80:
	{DBG_YY("simple_type = S8("<<TP_S8<<")");yyval.token_ = TP_S8;}
break;
case 81:
	{DBG_YY("simple_type = U16("<<TP_U16<<")");yyval.token_ =  TP_U16;}
break;
case 82:
	{DBG_YY("simple_type = S16("<<TP_S16<<")");yyval.token_ = TP_S16;}
break;
case 83:
	{DBG_YY("simple_type = U32("<<TP_U32<<")");yyval.token_ = TP_U32;}
break;
case 84:
	{DBG_YY("simple_type = S32("<<TP_S32<<")");yyval.token_ = TP_S32;}
break;
case 85:
	{DBG_YY("simple_type = U64("<<TP_U64<<")");yyval.token_ = TP_U64;}
break;
case 86:
	{DBG_YY("simple_type = S64("<<TP_S64<<")");yyval.token_ = TP_S64;}
break;
case 87:
	{DBG_YY("simple_type = STR("<<STR<<")");yyval.token_ = STR;}
break;
case 88:
	{DBG_YY("simple_type = STR1("<<STR1<<")");yyval.token_ = STR1;}
break;
case 89:
	{DBG_YY("simple_type = STR2("<<STR2<<")");yyval.token_ = STR2;}
break;
case 90:
	{DBG_YY("simple_type = STR4("<<STR4<<")");yyval.token_ = STR4;}
break;
case 91:
	{DBG_YY("simple_type = RAW("<<RAW<<")");yyval.token_ =  RAW;}
break;
case 92:
	{DBG_YY("simple_type = TCP("<<TCP<<")");yyval.token_ = TCP;}
break;
case 93:
	{DBG_YY("simple_type = UDP("<<UDP<<")");yyval.token_ = UDP;}
break;
case 94:
	{DBG_YY("comp_op = OP_LG("<<OP_LG<<")");yyval.token_ = OP_LG;}
break;
case 95:
	{DBG_YY("comp_op = OP_SM("<<OP_SM<<")");yyval.token_ = OP_SM;}
break;
case 96:
	{DBG_YY("comp_op = OP_LEQ("<<OP_LEQ<<")");yyval.token_ = OP_LEQ;}
break;
case 97:
	{DBG_YY("comp_op = OP_SEQ("<<OP_SEQ<<")");yyval.token_ = OP_SEQ;}
break;
case 98:
	{DBG_YY("comp_op = OP_EQ("<<OP_EQ<<")");yyval.token_ = OP_EQ;}
break;
case 99:
	{DBG_YY("comp_op = OP_NEQ("<<OP_NEQ<<")");yyval.token_ = OP_NEQ;}
break;
case 100:
	{DBG_YY("comp_op = OP_NOT("<<OP_NOT<<")");yyval.token_ = OP_NOT;}
break;
case 101:
	{DBG_YY("stream_op = OP_IN("<<OP_IN<<")");yyval.token_ = OP_IN;}
break;
case 102:
	{DBG_YY("stream_op = OP_OUT("<<OP_OUT<<")");yyval.token_ = OP_OUT;}
break;
case 103:
	{DBG_YY("stmt_sep = ;");}
break;
case 104:
	{DBG_YY("stmt_sep = NL");}
break;
case 105:
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
