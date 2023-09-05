#include "tui.h"

int menu(settings* s, celestials_settings* cs) {
  while (1) {
    char* options[5] = {
      "start",
      "configure screen",
      "configure celestials",
      "configure simulation",
      "quit",
    };

    int selected = selecto(options, 5);

    switch (selected) {
      case 0: return 0;
      case 1: screen(&s->screen_size, &s->zoom); break;
      case 2: celestials(cs); break;
      case 3: sim(&s->max_steps, &s->sim_length); break;
      case 4: return 1;
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

void sim(int* max_steps, double* sim_length) {
  while (1) {
    char* options[3];
    asprintf(&options[0], "max steps: %i", *max_steps);
    asprintf(&options[1], "sim length: %f", *sim_length);
    options[2] = "confirm";

    int selected = selecto(options, 3);

    switch (selected) {
      case(0): inputui("time step in seconds: ", max_steps); break;
      case(1): inputd("sim length in steps: ", sim_length); break;
      case(2): return;
    }

    free(options[0]);
    free(options[1]);
  }
}

void celestials(celestials_settings* cs) {
  while (1) {
    char* options[3];
    asprintf(&options[0], "fixed body index: %i", cs->fixed_body);
    asprintf(&options[1], "reference body index: %i", cs->reference_body);
    options[2] = "confirm";

    int selected = selecto(options, 3);

    switch (selected) {
      case(0): inputui("fixed body index: ", &cs->fixed_body); break;
      case(1): inputui("reference body index: ", &cs->reference_body); break;
      case(2): return;
    }

    free(options[0]);
    free(options[1]);
  }
}