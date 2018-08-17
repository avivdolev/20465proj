#include "header.h"

int assembler_first_go(Control *ctrl) {
  char line[MAX_SRC_LINE];
  char label[MAX_SRC_LINE] = "";
  string pt;

  while (get_line(ctrl, line)) {
    ctrl->line++;
    pt = line;
    /*Ignore comments and blank lines*/
    if (*line == COMMENT || *line == '\n')
      continue;

    /*Get label*/
    strcpy(label, line);
    if (find_label(ctrl, label)) {
      pt += strlen(label) + 1;
    } else {
      strcpy(label, "");
    }
    pt += trim(pt);
    if (!strlen(pt)) {
      add_error(ctrl, "Syntax error: can not add label to an empty line.\n");
      continue;
    }
    /*Data and Strings*/

    /*printf("label?: %d\t #%s\n", strlen(label) != 0, pt);*/
    /* printf("file: %s%s, line %d: %s\n", ctrl->filename, IN_EXT, ctrl->line,
           line);*/
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
  free_list(&ctrl->instruction_array);
  free_list(&ctrl->data_array);
  free_list(&ctrl->symbol_table);
  return;
}