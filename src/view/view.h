#pragma once

#include <SDL2/SDL.h>
#include <ncurses.h>
#include "../settings.h"

void render(settings s, celestials_settings cs);

void worldtod(vec3 coord, double zoom, int screen_radius);
void fixframe(vec3 coord, vec3 fixed_coord);
void draw_grid(SDL_Surface* surface);
void draw_circle(SDL_Surface* surface, int radius, vec3 coordinates, char color_i, char camera_axis, vec2i max, vec2i section);
void draw_lines(SDL_Surface* surface, vec3* coordinates, int num_steps, char color_i, char camera_axis, vec2i max, vec2i section);
int inscreen(vec2i p, vec2i max, vec2i min);
