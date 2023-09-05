#pragma once

#include <SDL2/SDL.h>
#include <ncurses.h>
#include "../settings.h"
#include "../space/celestials.h"

void render(settings s, celestials_settings cs);

void worldtod(vec3 coord, double zoom, int screen_radius);
void fixframe(vec3 coord, vec3 fixed_coord);
void draw_circle(SDL_Renderer *renderer, int radius, vec3 coordinates, int ci, int screen_radius);
void draw_lines(SDL_Renderer *renderer, vec3* coordinates, int num_steps, int ci, int screen_radius);
int inscreen(int x, int y, int size);
