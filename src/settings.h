#pragma once

#include "space/universe.h"

typedef struct {
  //screen
  int screen_size;
  double zoom;
  //simulation
  int max_steps; //the maximum amount of steps per celestial body saved in the memory
  int step_interval; //the interval between each step save 
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