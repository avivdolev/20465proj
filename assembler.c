/*
  Author: Aviv Dolev, ID 201534070
  Course: 20465 2018b
  MMN 14
*/

/*__________________ Assembler exectuable __________________*/

#include "header.h"

int main(int argc, char *argv[]) {

  /*Usage prompt*/
  if (!--argc) {
    printf("Usage: assembler [list of .as files without ext, space "
           "delimitered.]\n"
           "Example: assembler x y z\n");
    return OK;
  }

  /*Main loop over command line arguments*/
  while (argc--) {
    Control ctrl = CONTROL_INIT;
    Control *ctrlp = &ctrl;

    /*Get next source file*/
    if (get_next_file(ctrlp, *++argv)) {
      if (cleanup(ctrlp))
        PANIC("Error closing file!")
      else
        PANIC("Memory allocation problem!")
    }

    /*Start proccessing source file*/
    if (is_empty_list(&ctrlp->errors_array)) {
      if (assembler_first_go(ctrlp))
        PANIC("Memory allocation problem!")
    }

    /*Create output files*/
    if (is_empty_list(&ctrlp->errors_array)) {
      ;
    }
    /*Log errors, no output created*/
    else {
      dump_errors(ctrlp);
    }

    /*Clean everything before next source file*/
    if (cleanup(ctrlp))
      PANIC("Error closing files!")
  }

  return OK;
}
