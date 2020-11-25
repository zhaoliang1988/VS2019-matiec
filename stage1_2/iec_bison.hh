
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 255 "iec_bison.yy"

/* define a new data type to store the locations, so we can also store
 * the filename in which the token is expressed.
 */
/* NOTE: since this code will be placed in the iec_bison.hh header file,
 * as well as the iec.cc file that also includes the iec_bison.hh header file,
 * declaring the typedef struct yyltype__local here would result in a 
 * compilation error when compiling iec.cc, as this struct would be
 * declared twice.
 * We therefore use the #if !defined YYLTYPE ...
 * to make sure only the first declaration is parsed by the C++ compiler.
 */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE {
    int         first_line;
    int         first_column;
    const char *first_file;
    long int    first_order;
    int         last_line;
    int         last_column;
    const char *last_file;
    long int    last_order;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 0
#endif




/* Line 1676 of yacc.c  */
#line 71 "F:/vsproject/matiec-vs/stage1_2/iec_bison.hh"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_INPUT = 0,
     BOGUS_TOKEN_ID = 258,
     prev_declared_variable_name_token = 259,
     prev_declared_direct_variable_token = 260,
     prev_declared_fb_name_token = 261,
     prev_declared_simple_type_name_token = 262,
     prev_declared_subrange_type_name_token = 263,
     prev_declared_enumerated_type_name_token = 264,
     prev_declared_array_type_name_token = 265,
     prev_declared_structure_type_name_token = 266,
     prev_declared_string_type_name_token = 267,
     prev_declared_ref_type_name_token = 268,
     prev_declared_derived_function_name_token = 269,
     prev_declared_derived_function_block_name_token = 270,
     prev_declared_program_type_name_token = 271,
     start_ST_body_token = 272,
     start_IL_body_token = 273,
     disable_code_generation_pragma_token = 274,
     enable_code_generation_pragma_token = 275,
     pragma_token = 276,
     EN = 277,
     ENO = 278,
     REF = 279,
     DREF = 280,
     REF_TO = 281,
     NULL_token = 282,
     identifier_token = 283,
     integer_token = 284,
     binary_integer_token = 285,
     octal_integer_token = 286,
     hex_integer_token = 287,
     real_token = 288,
     safeboolean_true_literal_token = 289,
     safeboolean_false_literal_token = 290,
     boolean_true_literal_token = 291,
     boolean_false_literal_token = 292,
     FALSE = 293,
     TRUE = 294,
     single_byte_character_string_token = 295,
     double_byte_character_string_token = 296,
     fixed_point_token = 297,
     fixed_point_d_token = 298,
     integer_d_token = 299,
     fixed_point_h_token = 300,
     integer_h_token = 301,
     fixed_point_m_token = 302,
     integer_m_token = 303,
     fixed_point_s_token = 304,
     integer_s_token = 305,
     fixed_point_ms_token = 306,
     integer_ms_token = 307,
     end_interval_token = 308,
     erroneous_interval_token = 309,
     T_SHARP = 310,
     D_SHARP = 311,
     BYTE = 312,
     WORD = 313,
     DWORD = 314,
     LWORD = 315,
     LREAL = 316,
     REAL = 317,
     SINT = 318,
     INT = 319,
     DINT = 320,
     LINT = 321,
     USINT = 322,
     UINT = 323,
     UDINT = 324,
     ULINT = 325,
     WSTRING = 326,
     STRING = 327,
     BOOL = 328,
     TIME = 329,
     DATE = 330,
     DATE_AND_TIME = 331,
     DT = 332,
     TIME_OF_DAY = 333,
     TOD = 334,
     VOID = 335,
     SAFEBYTE = 336,
     SAFEWORD = 337,
     SAFEDWORD = 338,
     SAFELWORD = 339,
     SAFELREAL = 340,
     SAFEREAL = 341,
     SAFESINT = 342,
     SAFEINT = 343,
     SAFEDINT = 344,
     SAFELINT = 345,
     SAFEUSINT = 346,
     SAFEUINT = 347,
     SAFEUDINT = 348,
     SAFEULINT = 349,
     SAFEWSTRING = 350,
     SAFESTRING = 351,
     SAFEBOOL = 352,
     SAFETIME = 353,
     SAFEDATE = 354,
     SAFEDATE_AND_TIME = 355,
     SAFEDT = 356,
     SAFETIME_OF_DAY = 357,
     SAFETOD = 358,
     ANY = 359,
     ANY_DERIVED = 360,
     ANY_ELEMENTARY = 361,
     ANY_MAGNITUDE = 362,
     ANY_NUM = 363,
     ANY_REAL = 364,
     ANY_INT = 365,
     ANY_BIT = 366,
     ANY_STRING = 367,
     ANY_DATE = 368,
     ASSIGN = 369,
     DOTDOT = 370,
     TYPE = 371,
     END_TYPE = 372,
     ARRAY = 373,
     OF = 374,
     STRUCT = 375,
     END_STRUCT = 376,
     direct_variable_token = 377,
     incompl_location_token = 378,
     VAR_INPUT = 379,
     VAR_OUTPUT = 380,
     VAR_IN_OUT = 381,
     VAR_EXTERNAL = 382,
     VAR_GLOBAL = 383,
     END_VAR = 384,
     RETAIN = 385,
     NON_RETAIN = 386,
     R_EDGE = 387,
     F_EDGE = 388,
     AT = 389,
     standard_function_name_token = 390,
     FUNCTION = 391,
     END_FUNCTION = 392,
     CONSTANT = 393,
     standard_function_block_name_token = 394,
     FUNCTION_BLOCK = 395,
     END_FUNCTION_BLOCK = 396,
     VAR_TEMP = 397,
     VAR = 398,
     PROGRAM = 399,
     END_PROGRAM = 400,
     ACTION = 401,
     END_ACTION = 402,
     TRANSITION = 403,
     END_TRANSITION = 404,
     FROM = 405,
     TO = 406,
     PRIORITY = 407,
     INITIAL_STEP = 408,
     STEP = 409,
     END_STEP = 410,
     L = 411,
     D = 412,
     SD = 413,
     DS = 414,
     SL = 415,
     N = 416,
     P = 417,
     P0 = 418,
     P1 = 419,
     prev_declared_global_var_name_token = 420,
     prev_declared_program_name_token = 421,
     prev_declared_resource_name_token = 422,
     prev_declared_configuration_name_token = 423,
     CONFIGURATION = 424,
     END_CONFIGURATION = 425,
     TASK = 426,
     RESOURCE = 427,
     ON = 428,
     END_RESOURCE = 429,
     VAR_CONFIG = 430,
     VAR_ACCESS = 431,
     WITH = 432,
     SINGLE = 433,
     INTERVAL = 434,
     READ_WRITE = 435,
     READ_ONLY = 436,
     EOL = 437,
     sendto_identifier_token = 438,
     LD = 439,
     LDN = 440,
     ST = 441,
     STN = 442,
     NOT = 443,
     S = 444,
     R = 445,
     S1 = 446,
     R1 = 447,
     CLK = 448,
     CU = 449,
     CD = 450,
     PV = 451,
     IN = 452,
     PT = 453,
     AND = 454,
     AND2 = 455,
     OR = 456,
     XOR = 457,
     ANDN = 458,
     ANDN2 = 459,
     ORN = 460,
     XORN = 461,
     ADD = 462,
     SUB = 463,
     MUL = 464,
     DIV = 465,
     MOD = 466,
     GT = 467,
     GE = 468,
     EQ = 469,
     LT = 470,
     LE = 471,
     NE = 472,
     CAL = 473,
     CALC = 474,
     CALCN = 475,
     RET = 476,
     RETC = 477,
     RETCN = 478,
     JMP = 479,
     JMPC = 480,
     JMPCN = 481,
     SENDTO = 482,
     OPER_NE = 483,
     OPER_GE = 484,
     OPER_LE = 485,
     OPER_EXP = 486,
     RETURN = 487,
     IF = 488,
     THEN = 489,
     ELSIF = 490,
     ELSE = 491,
     END_IF = 492,
     CASE = 493,
     END_CASE = 494,
     FOR = 495,
     BY = 496,
     DO = 497,
     END_FOR = 498,
     WHILE = 499,
     END_WHILE = 500,
     REPEAT = 501,
     UNTIL = 502,
     END_REPEAT = 503,
     EXIT = 504
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 286 "iec_bison.yy"

    symbol_c 	*leaf;
    list_c	*list;
    char 	*ID;	/* token value */



/* Line 1676 of yacc.c  */
#line 346 "F:/vsproject/matiec-vs/stage1_2/iec_bison.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

