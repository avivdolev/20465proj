#include "header.h"

boolean find_label(Control *ctrl, string s) {
  string token;
  string end = QM(LABEL_END);

  if (!strchr(s, LABEL_END) || !(token = strtok(s, end)))
    /*There is no label*/
    return FALSE;
    
  /*Detect instruction*/
  if (isReservedWord(ctrl, token, In) != EOIL) {
    add_error(ctrl, "Illegal label: can not be a reserved assembly word "
                    "(instruction).\n");
    return FALSE;
  }

  if (edge_case_string(ctrl, token)) {
    return FALSE;
  }

  /*Check if label is legal*/
  if (!isalpha(*token))
    add_error(ctrl, "Illegal label: must start with a letter.\n");

  if (strlen(token) > MAX_LABEL)
    add_error(ctrl, "Illegal label: too long. Max label length is " Q(
                        MAX_LABEL) ".\n");

  if (isReservedWord(ctrl, token, Op) != EOCL) {
    add_error(
        ctrl,
        "Illegal label: can not be a reserved assembly word (operation).\n");
    return FALSE;
  }

  if (isReservedWord(ctrl, token, Re) != EORL) {
    add_error(
        ctrl,
        "Illegal label: can not be a reserved assembly word (register).\n");
    return FALSE;
  }

  for (; *token; token++) {
    if (!isalnum(*token)) {
      add_error(
          ctrl,
          "Illegal label: can not contain non alphanumeric characters.\n");
      return FALSE;
    }
  }
  return !is_empty_list(&ctrl->errors_array);
}


int isReservedWord(Control *ctrl, string s, int EOL) {
  int i = 0;
  string *pt;
  switch (EOL) {
  case Op:
    EOL = EOCL;
    pt = ctrl->ops_array;
    break;
  case In:
    EOL = EOIL;
    pt = ctrl->instnames_array;
    break;
  case Re:
    EOL = EORL;
    pt = ctrl->regs_array;
    break;
  }

  for (i = 0; i < EOL && strcmp(s, *(pt + i)); i++)
    ;

  return i;
}

boolean edge_case_string(Control *ctrl, string token) {
  int len = strlen(ctrl->instnames_array[i_string]);
  return !strncmp(token, ctrl->instnames_array[i_string], len);
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
