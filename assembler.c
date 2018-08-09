/*
  Author: Aviv Dolev, ID 201534070
  Course: 20465 2018b
  MMN 14
*/

#include "header.h"

int main(int argc, char *argv[]) {
  
  if (!--argc) {
    printf("Usage: assembler [list of .as files without ext, space "
           "delimitered.]\n"
           "Example: assembler x y z\n");
    return OK;
  }

  while (argc--) {
    Control ctrl = CONTROL_INIT;
    Control *ctrlp = &ctrl;

    if (get_next_file(ctrlp, *++argv)) {
      if (cleanup(ctrlp))
        PANIC("Error closing file!")
      else
        PANIC ("Memory allocation problem!")
    }



    if (!is_empty_list(&ctrlp->errors_array)) {
      dump_errors(ctrlp);
      if (cleanup(ctrlp))
        PANIC("Error closing file!")
    }
  }

  return OK;
}
