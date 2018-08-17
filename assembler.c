/*
  Author: Aviv Dolev, ID 201534070
  Course: 20465 2018b
  MMN 14
*/

/*__________________ Assembler exectuable __________________*/

#include "header.h"

int main(int argc, char *argv[]) {

  /*Check command line argument, if absent prompt message and exit.*/
  if (!--argc) {
    printf(PROMPT);
    return OK;
  }

  /*Main loop over command line arguments*/
  while (argc--) {
    Control ctrl = CONTROL_INIT;
    Control *ctrlp = &ctrl;
    
    /*Get next source file*/
    get_next_file(ctrlp, *++argv);

    /*Start proccessing source file*/
    if (is_empty_list(&ctrlp->errors_array)) {
      assembler_first_go(ctrlp);
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
    cleanup(ctrlp);
  }

  return OK;
}
