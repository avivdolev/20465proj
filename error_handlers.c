#include "header.h"

void add_error(Control *ctrl, string m) {
  /*
  Description: Add an error to errors array.
  Input: Control object, file name, line number and error message.
  Output: void.
  */
  Error e;
  Error *ep = &e;

  strncpy(ep->file, ctrl->filename, MAX_FILE_NAME);
  ep->line = ctrl->line;
  strncpy(ep->message, m, MAX_ERROR_MESSAGE);

  add_item(&ctrl->errors_array, ep, sizeof(e));

  return;
}

void dump_errors(Control *ctrl) {
  walk_list(&ctrl->errors_array, &print_error);
}

void print_error(void *e) {
  Error *ep = (Error *)e;
  fprintf(LOGFILE, "%s%s: line %d: %s", ep->file, IN_EXT, ep->line,
          ep->message);
  return;
}
