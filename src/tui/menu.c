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
    char* options[8];
    asprintf(&options[0], "fixed body index: %i\n", cs->fixed_body);
    asprintf(&options[1], "ship x coordinate: %f", cs->celestials[2].initial_coordinates[x]);
    asprintf(&options[2], "ship y coordinate: %f", cs->celestials[2].initial_coordinates[y]);
    asprintf(&options[3], "ship z coordinate: %f", cs->celestials[2].initial_coordinates[z]);
    asprintf(&options[4], "ship x velocity: %f", cs->celestials[2].initial_velocity[x]);
    asprintf(&options[5], "ship y velocity: %f", cs->celestials[2].initial_velocity[y]);
    asprintf(&options[6], "ship z velocity: %f", cs->celestials[2].initial_velocity[z]);
    options[7] = "confirm";

    int selected = selecto(options, 8);

    switch (selected) {
      case(0): inputui("fixed body index: ", &cs->fixed_body); break;
      case(1): inputd("ship x coordinates: ", &cs->celestials[2].initial_coordinates[x]); break;
      case(2): inputd("ship y coordinates: ", &cs->celestials[2].initial_coordinates[y]); break;
      case(3): inputd("ship z coordinates: ", &cs->celestials[2].initial_coordinates[z]); break;
      case(4): inputd("ship x velocity: ", &cs->celestials[2].initial_velocity[x]); break;
      case(5): inputd("ship y velocity: ", &cs->celestials[2].initial_velocity[y]); break;
      case(6): inputd("ship z velocity: ", &cs->celestials[2].initial_velocity[z]); break;
      case(7): return;
    }

    free(options[0]);
    free(options[1]);
    free(options[2]);
    free(options[3]);
    free(options[4]);
    free(options[5]);
    free(options[6]);
  }
}

void presim(int* pre_sim) {
  *pre_sim = 1;
}