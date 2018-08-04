/*
  Author: Aviv Dolev, ID 201534070
  Course: 20465 2018b
  MMN 14
*/

#include "header.h"

int main(int argc, char *argv[]) {

  if (!--argc) {
    printf("Usage: assmbler [list of .as files without ext, space "
           "delimitered.]\n"
           "Example: assembler x y z\n");
    return OK;
  }

  while (argc--) {
    Control ctrl = CONTROL_INIT;
    Control *ctrlp = &ctrl;

    if (get_next_file(ctrlp, *++argv)) {
      if (cleanup(ctrlp)) {
        fprintf(LOGFILE, "%s\n", "Error closing file!");
        return !OK;
      }
      fprintf(LOGFILE, "%s\n", "Memory allocation problem!");
      return !OK;
    }
    if (!is_empty_list(&ctrlp->errors_array)) {
      dump_erros(ctrlp);
      if (cleanup(ctrlp)) {
        fprintf(LOGFILE, "%s\n", "Error closing file!");
        return !OK;
      }
    }
  }

  return OK;
}
