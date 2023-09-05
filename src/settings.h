#pragma once

#include "space/celestials.h"

typedef struct {
  //screen
  int screen_size;
  double zoom;
  //simulation
  int max_steps;
  double sim_length;
  //view settings
  int num_steps;
  double scale;
} settings;

typedef struct {
  int num_celestials;
  celestial* celestials;
  int center_body;
  int fixed_body;
  int reference_body;
} celestials_settings;