#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include "../settings.h"
#include "../space/celestials.h"

int menu(settings* s, celestials_settings* cs);

void screen(int* screen_size, double* zoom);
void sim(int* max_steps, double* sim_length);
void celestials(celestials_settings* cs);

int selecto(char** options, int num_options);
void inputui(char* text, int* var);
void inputd(char* text, double* var);