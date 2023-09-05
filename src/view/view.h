#pragma once

#include <SDL2/SDL.h>
#include <ncurses.h>
#include "../settings.h"
#include "../space/celestials.h"

void render(settings s, celestials_settings cs);

void worldtod(vec3 coord, double zoom, int screen_radius);
void fixframe(vec3 coord, vec3 fixed_coord);
void draw_circle(SDL_Surface* surface, int radius, vec3 coordinates, char ci);
void draw_line(SDL_Surface* surface, vec3 c1, vec3 c2, char ci);
void draw_lines(SDL_Surface* surface, vec3* coordinates, int num_steps, char ci);
int inscreen(int x, int y, int size);
