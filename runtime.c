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
      add_error(ctrl, ctrl->filename, ctrl->line,
                "Syntax error: can not add label to an empty line.\n");
    }
    /*printf("label?: %d\t #%s\n", strlen(label) != 0, pt);*/
    /* printf("file: %s%s, line %d: %s\n", ctrl->filename, IN_EXT, ctrl->line,
           line);*/
  }
  return OK;
}

boolean find_label(Control *ctrl, string s) {
  string token;
  int i = 0;
  char end = LABEL_END;

  if (!strchr(s, end) || !(token = strtok(s, &end)))
    /*There is no label*/
    return FALSE;

  /*Detect instruction*/
  for (i = 0; i < EOIL; i++)
    if (!strncmp(token, *(ctrl->instnames_array + i),
                 strlen(*(ctrl->instnames_array + i)))) {
      if (!strcmp(token, *(ctrl->instnames_array + i)))
        add_error(ctrl, ctrl->filename, ctrl->line,
                  "Illegal label: can not be a reserved assembly word.\n");
      return FALSE;
    }
  /*Check if label is legal*/
  if (!isalpha(*token))
    add_error(ctrl, ctrl->filename, ctrl->line,
              "Illegal label: must start with a letter.\n");
  if (strlen(token) > MAX_LABEL)
    add_error(
        ctrl, ctrl->filename, ctrl->line,
        "Illegal label: too long. Max label length is " Q(MAX_LABEL) ".\n");
  for (i = 0; i < EOCL; i++)
    if (!strcmp(token, *(ctrl->ops_array + i))) {
      add_error(ctrl, ctrl->filename, ctrl->line,
                "Illegal label: can not be a reserved assembly word.\n");
      return FALSE;
    }

  for (; *token; token++) {
    if (!isalnum(*token)) {
      add_error(
          ctrl, ctrl->filename, ctrl->line,
          "Illegal label: can not contain non alphanumeric characters.\n");
      return FALSE;
    }
  }
  return is_empty_list(&ctrl->errors_array);
}

int trim(string s) {
  /*
  Description: Trims blank chars from start of s.
  Input: String s.
  Output: Number of blanks to trim (to be used as addition to a pointer).
  */
  int i;
  for (i = 0; isspace(*(s + i)) && *(s + i) != '\n'; i++)
    ;
  return i;
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