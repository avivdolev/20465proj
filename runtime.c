#include "header.h"

int assembler_first_go(Control *ctrl) {
  char line[MAX_SRC_LINE];
  while (get_line(ctrl, line)) {
    ctrl->line++;

    /*Ignore comments and blank lines*/
    if (*line == COMMENT || *line == '\n')
      continue;
    

    printf("file: %s%s, line %d: %s\n",ctrl->filename, IN_EXT,ctrl->line,line);


  }
  return OK;
}

void cleanup(Control *ctrl) {
  /*
  Description: Cleanup run-time enviornment: free allocated memory, close files.
  Input: Control object.
  Output: void.
  */
  if (ctrl->fp)
    if (fclose(ctrl->fp) == EOF)
      PANIC("Error closing files, assembler crashed!")
  free_list(&ctrl->errors_array);
  free_list(&ctrl->inst_array);
  free_list(&ctrl->data_array);
  free_list(&ctrl->symbol_table);
  return;
}