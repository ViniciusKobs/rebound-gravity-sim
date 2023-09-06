#include "tui.h"

int menu(settings* s, celestials_settings* cs, int* pre_sim) {
  while (1) {
    char* options[6] = {
      "start",
      "pre-simulate",
      "configure screen",
      "configure celestials",
      "configure simulation",
      "quit",
    };

    int selected = selecto(options, 6);

    switch (selected) {
      case 0: return 0;
      case 1: presim(pre_sim); return 0;
      case 2: screen(&s->screen_size, &s->zoom); break;
      case 3: celestials(cs); break;
      case 4: sim(&s->max_steps, &s->step_interval, &s->sim_length); break;
      case 5: return 1;
    }
  }
}

void screen(int* screen_size, double* zoom) {
  while (1) {
    char* options[3];
    asprintf(&options[0], "screen size: %ipx", *screen_size);
    asprintf(&options[1], "zoom: %f", *zoom);
    options[2] = "confirm";

    int selected = selecto(options, 3);

    switch (selected) {
      case(0): inputui("screen size in pixels: ", screen_size); break;
      case(1): inputd("zoom: ", zoom); break;
      case(2): return;
    }

    free(options[0]);
    free(options[1]);
  }
}

void sim(int* max_steps, int* step_interval, double* sim_length) {
  while (1) {
    char* options[4];
    asprintf(&options[0], "max steps: %i", *max_steps);
    asprintf(&options[1], "step interval: %i", *step_interval);
    asprintf(&options[2], "sim length: %f", *sim_length);
    options[3] = "confirm";

    int selected = selecto(options, 4);

    switch (selected) {
      case(0): inputui("max steps: ", max_steps); break;
      case(1): inputui("step interval: ", step_interval); break;
      case(2): inputd("sim length in steps: ", sim_length); break;
      case(3): return;
    }

    free(options[0]);
    free(options[1]);
    free(options[2]);
  }
}

void celestials(celestials_settings* cs) {
  while (1) {
    char* options[2];
    asprintf(&options[0], "fixed body index: %i", cs->fixed_body);
    options[1] = "confirm";

    int selected = selecto(options, 2);

    switch (selected) {
      case(0): inputui("fixed body index: ", &cs->fixed_body); break;
      case(1): return;
    }

    free(options[0]);
  }
}

void presim(int* pre_sim) {
  *pre_sim = 1;
}