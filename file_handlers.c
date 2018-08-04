#include "header.h"

int get_next_file(Control *ctrl, string file) {
  /*
  Description: Try to open next input file. If failed, add an error.
  Input: Control object, filename.
  Output: !OK if memory allocation problem occured.
  */

  string path;
  if (strlen(file) > MAX_FILE_NAME)
    return add_error(ctrl, file, ctrl->line,
                     "Max filename length is: " Q(MAX_FILE_NAME) "\n");

  MALLOC(path, char, strlen(file) + strlen(IN_EXT "\0"));

  strcpy(ctrl->filename, file);
  strcpy(path, file);

  if (!(ctrl->fp = fopen(strcat(path, IN_EXT), "r"))) 
    return add_error(ctrl, file, ctrl->line,
                     "File does not exist.\n");
  free(path);
  return OK;
}