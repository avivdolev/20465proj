#include "header.h"

void get_next_file(Control *ctrl, string file) {
  /*
  Description: Try to open next input file. If failed, add an error.
  Input: Control object, filename (cli argument).
  Output: void.
  */

  int c;
  string path;

  if (strlen(file) > MAX_FILE_NAME) {
    add_error(ctrl, file, ctrl->line,
                     "Max filename length is: " Q(MAX_FILE_NAME) "\n");
    return;
  }

  MALLOC(path, char, strlen(file) + strlen(IN_EXT "\0"));

  strcpy(ctrl->filename, file);
  strcpy(path, file);

  if (!(ctrl->fp = fopen(strcat(path, IN_EXT), "r")))
    add_error(ctrl, file, ctrl->line, "File does not exist.\n");

  else if ((c = fgetc(ctrl->fp) == EOF)) {
    add_error(ctrl, file, ctrl->line, "File is empty.\n");
  }

  else if (fseek(ctrl->fp, 0, SEEK_SET)) {
    add_error(ctrl, file, ctrl->line, "Problem handling file.\n");
  }

  free(path);
  return;
}

string get_line(Control *ctrl, string s) {
  /*
  Description: Get next line from source file, trim leading spaces and ending
  newline.
  Input: Control object, string to store line.
  Output: Pointer to line or NULL if EOF or error occurred.
  */
  int i = 0;
  string newline;

  if (!fgets(s, MAX_SRC_LINE, ctrl->fp))
    return NULL;
  for (i = 0; isspace(*(s + i)) && *(s+i) != '\n'; i++)
    ;
  
  newline = strchr(s, '\n');
  if (newline != (s+i) && newline != NULL)
    *(strchr(s, '\n')) = '\0';
  strcpy(s, s + i);
  return s;
}