#include "tui.h"

int selecto(char** options, int num_options) {
  flushinp();
  noecho();
  int selected = 0;
  int key;
  while (1) {
    clear();
    for (int i = 0; i < num_options; i++) {
      if (i == selected) printw("-> %s\n", options[i]);
      else printw("   %s\n", options[i]);
    }
    refresh();
    key = getch();
    if (key == KEY_UP) selected = (selected + num_options - 1) % num_options; 
    else if (key == KEY_DOWN) selected = (selected + 1) % num_options; 
    else if (key == 10) return selected;
  }
}

void inputui(char* text, int* var) {
  echo();
  printw("%s", text);
  refresh();
  char input[100];
  getstr(input);
  *var = atoi(input);
}

void inputd(char* text, double* var) {
  echo();
  printw("%s", text);
  refresh();
  char input[100];
  getstr(input);
  *var = atof(input);
}