#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "tui/tui.h"
#include "space/universe.h"
#include "sim/sim.h"
#include "view/view.h"

void info(settings s, celestials_settings cs, int t);

int main() {
  settings s = {1000, .8, 2500, 1, 2*PI, 0, 0};
  celestials_settings cs = {3, NULL, 0, 0, 1};

  celestial* c = malloc(sizeof (celestial) * cs.num_celestials);
  c[0] = (celestial) {5.972E24, 6371E3, {0}, {0}, NULL, NULL};
  c[1] = (celestial) {7.347E22, 1734E3, {0}, {0}, NULL, NULL};
  c[2] = (celestial) {0, 50, {0, -(6371E3 + 300E3), 0}, {10909, 0, 0}, NULL};
  orbit moon = {384748E3, 0.054, 0, 0, 0, .5};
  c[1].initial_orbit = &moon;

  cs.celestials = c;

  initscr();
  keypad(stdscr, TRUE);
  cbreak();

  int quit = 0;
  int pre_sim = 0;
  while(!quit) {
    quit = menu(&s, &cs, &pre_sim);
    if (quit) break;

    if (pre_sim) {
      clear();
      simulate(&s, &cs, 1);
      printw("-> continue");
      refresh();

      flushinp();
      int key = 0;
      while(key != 10) {
        key = getch();
      }
      
      pre_sim = 0;
    } else {
      for (int i = 0; i < cs.num_celestials; i++) {
        c[i].coordinates = malloc(sizeof (vec3) * s.max_steps);
      }

      clear();
      simulate(&s, &cs, 0);
      refresh();

      render(s, cs);

      for (int i = 0; i < cs.num_celestials; i++) {
        free(c[i].coordinates);
      }
    }
  }

  endwin();
  free(cs.celestials);
}

void info(settings s, celestials_settings cs, int t) {
  for (int i = 0; i < cs.num_celestials; i++) {
    for (int j = 0; j < s.num_steps; j++) {
      clear();
      printw("%i: %f, %f, %f\n", i, cs.celestials[i].coordinates[j][x], cs.celestials[i].coordinates[j][y], cs.celestials[i].coordinates[j][z]);
      napms(t);
      refresh();
    }
  }
}