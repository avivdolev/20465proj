/*
Headers file for mmn14
*/

/*__________________ Prevent header duplication __________________*/
#ifndef FILE_H
#define FILE_H

/*__________________ Libraries __________________*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*__________________ Definitions __________________*/
#define WORD_SIZE 14
#define ZERO '.'
#define ONE '/'
#define INSTANT '#'
#define COMMENT ';'
#define SEP ','
#define LABEL_END ':'
#define INST '.'
#define FIRST_ADDR 100
#define IN_EXT ".as"
#define OUT_EXT ".ob"
#define EXT_EXT ".ext"
#define ENT_EXT ".ent"
#define TRUE 1
#define FALSE 0
#define OK 0
#define LOGFILE stderr

enum encodings { A, E, R };

/*__________________ Macros __________________*/

/*Usage prompt: if assembler called without arguments.*/
#define PROMPT                                                                 \
  "Usage: assembler [list of .as files without ext, space "                    \
  "delimitered.]\n"                                                            \
  "Example: assembler x y z\n"

/*Throw error and exit main function*/
#define PANIC(message)                                                         \
  {                                                                            \
    fprintf(LOGFILE, "%s\n", message);                                         \
    exit(!OK);                                                                 \
  }

/*Use malloc and exit if allocation failed*/
#define MALLOC(dst, pntr_type, size)                                           \
  {                                                                            \
    dst = (pntr_type *)malloc(size);                                           \
    if (dst == NULL)                                                           \
      PANIC("Memory allocation problem, assembler crashed!")                   \
  }

/*List of assembler operations:*/
#define OP_NAMES                                                               \
  QUOTE(mov)                                                                   \
  QUOTE(cmp)                                                                   \
  QUOTE(add)                                                                   \
  QUOTE(sub)                                                                   \
  QUOTE(not)                                                                   \
  QUOTE(clr)                                                                   \
  QUOTE(lea)                                                                   \
  QUOTE(inc)                                                                   \
  QUOTE(dec)                                                                   \
  QUOTE(jmp)                                                                   \
  QUOTE(bne)                                                                   \
  QUOTE(red)                                                                   \
  QUOTE(prn)                                                                   \
  QUOTE(jsr)                                                                   \
  QUOTE(rts)                                                                   \
  QUOTE(stop)                                                                  \
  Q(EOCL)
/*End of Command List*/

#define INST_NAMES                                                             \
  QUOTE(.string)                                                          \
  QUOTE(.data)                                                            \
  QUOTE(.entry)                                                           \
  QUOTE(.extern)                                                          \
  Q(EOIL)
/*End of Instructions List*/

/*
Set of macros to create enum and string array with matching names,
so we can easily use "array[operation]" and get the operation as
a string.
*/
#define QUOTE(m) m ## _,
/*without quotes, to be used with enum*/
#define Q(m) m

enum { OP_NAMES };
enum { i_string, i_data , i_extern, i_entry , EOIL};
#undef QUOTE
#undef Q
#define QUOTE(m) #m, /*add quotes to be used as list of strings*/
#define Q(m) #m

/*__________________ Limits __________________*/
#define OPS_NUMBER (EOCL + 1)
#define INST_NUMBER (EOIL + 1)
#define MAX_SRC_LINE 81
#define MAX_LABEL 32
#define MAX_OPERATION 5
#define MAX_INSTRUCTION 10
#define MAX_FILE_NAME 80
#define MAX_ERROR_MESSAGE 60

/*__________________ Data Structures __________________*/
typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
} List;

/*__________________ Types __________________*/

/*Basic types*/
typedef char boolean;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef char *string;

/*Memory word*/
typedef ushort word;

/*Error info*/
typedef struct Error {
  char file[MAX_FILE_NAME];
  int line;
  char message[MAX_ERROR_MESSAGE];
} Error;

/*Symbol*/
typedef struct Symbol {
  char name[MAX_LABEL];
  char encoding;
  int address;
  boolean isdata;
} Symbol;

/*Control - structure to hold assembler run-time variables*/
typedef struct Control {
  string ops_array[OPS_NUMBER];
  string instnames_array[INST_NUMBER];
  char filename[MAX_FILE_NAME];
  FILE *fp;
  uint line;
  uint IC;
  uint DC;
  List errors_array;
  List inst_array;
  List data_array;
  List symbol_table;

} Control;

/*Macro to initialize control object*/
#define CONTROL_INIT                                                           \
  {                                                                            \
    {OP_NAMES}, { INST_NAMES }                                                 \
  }

/*__________________ Functions __________________*/
/*Detailed documentation inside each file*/

/*list.c*/
void add_item(List *list, void *data, size_t datasize);
void free_list(List *list);
boolean is_empty_list(List *list);
void print_list(List *list);
void walk_list(List *list, void (*action)(void *));

/*file_handlers.c*/
void get_next_file(Control *ctrl, string file);
string get_line(Control *ctrl, string s);

/*error_handlers.c*/
void add_error(Control *ctrl, string file, int line, string m);
void print_error(void *e);
void dump_errors(Control *ctrl);

/*runtime.c*/
int assembler_first_go(Control *ctrl);
boolean find_label(Control *ctrl, string s);
int trim(string s);
void cleanup(Control *ctrl);

/*__________________ End of header file __________________*/

#endif