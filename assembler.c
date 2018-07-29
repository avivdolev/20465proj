/*
  Author: Aviv Dolev, ID 201534070
  Course: 20465 2018b
  MMN 14
*/

#include "header.h"

int main(int argc, char *argv[]) {

  Control ctrl = CONTROL_INIT;
  
  printf("%s %d\n", ctrl.ops_array[bne], (int) sizeof(ctrl));
  test(&ctrl);



  free_list(&ctrl.inst_array);
  return 0;
}

void test(Control *ctrl) {
  double x = 7;
  double y;
  add_item(&ctrl->inst_array, &x, sizeof(x));
  y=9;
  add_item(&ctrl->inst_array, &y, sizeof(x));
  y=20;
  add_item(&ctrl->inst_array, &y, sizeof(x));
  print_list(&ctrl->inst_array);
  return;
}