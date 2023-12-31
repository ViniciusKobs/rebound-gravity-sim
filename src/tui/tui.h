#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include "../settings.h"

// menu.c
int menu(settings* s, celestials_settings* cs, int* pre_sim);
void screen(int* screen_size, double* zoom);
void sim(int* max_steps, int* step_interval, double* sim_length);
void celestials(celestials_settings* cs);
void presim(int* pre_sim);
// tui.c
int selecto(char** options, int num_options);
void inputui(char* text, int* var);
void inputd(char* text, double* var);