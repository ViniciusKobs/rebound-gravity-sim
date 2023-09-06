#pragma once

#include <ncurses.h>
#include "../vector/vector.h"
#include "../settings.h"

void simulate(settings* s, celestials_settings* cs, int pre_sim);
int calculate_num_steps(int steps_done, int step_interval);
