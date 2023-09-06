#include "view.h"
#include <SDL2/SDL_surface.h>

void render(settings s, celestials_settings cs) {
  int screen_radius = s.screen_size / 2;
  celestial* c = cs.celestials;

  for (int i = 0; i < s.num_steps; i++) {
    for (int j = 0; j < cs.num_celestials; j++) {
      worldtod(c[j].coordinates[i], s.zoom, screen_radius);
    }
    vec3 fixed_frame = {c[cs.fixed_body].coordinates[i][x], c[cs.fixed_body].coordinates[i][y], c[cs.fixed_body].coordinates[i][z]};
    vec3subd(fixed_frame, screen_radius);
    for (int j = 0; j < cs.num_celestials; j++) {
      fixframe(c[j].coordinates[i], fixed_frame);
    }
  }

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Gravity Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s.screen_size, s.screen_size, 0);
  SDL_Surface* surface = SDL_CreateRGBSurface(0, s.screen_size, s.screen_size, 8, 0, 0, 0, 0);
  SDL_Event event;

  SDL_Color colors[256];
  colors[0].r = 0; colors[0].g = 0; colors[0].b = 0;
  colors[1].r = 0; colors[1].g = 0; colors[1].b = 255;
  colors[2].r = 0; colors[2].g = 255; colors[2].b = 0;
  colors[3].r = 255; colors[3].g = 0; colors[3].b = 0;
  SDL_SetPaletteColors(surface->format->palette, colors, 0, 4);

  SDL_FillRect(surface, NULL, 0);
  for (int i = 0; i < cs.num_celestials; i++) {
    draw_circle(surface, (c[i].radius / s.scale) * screen_radius * s.zoom, c[i].coordinates[s.num_steps - 1], (char)i + 1);
    draw_lines(surface, c[i].coordinates, s.num_steps, (char)i + 1);
  }

  int key = 0;
  int quit = 0;
  while (!quit) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    SDL_BlitSurface(surface, NULL, windowSurface, NULL);
    SDL_UpdateWindowSurface(window);
  }

  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void draw_point(SDL_Surface* surface, vec2i p, char ci) {
  if (inscreen(p[x], p[y], surface->w)) {
    char* pixel = (char*)surface->pixels + p[y] * surface->pitch + p[x];
    *pixel = ci;
  }
}

void draw_line(SDL_Surface* surface, vec3 c1, vec3 c2, char ci) {
  vec2i p1 = {(int)c1[x], (int)c1[y]};
  vec2i p2 = {(int)c2[x], (int)c2[y]};
  vec2i d = {abs((p2[x] - p1[x])), abs((p2[y] - p1[y]))};
  vec2i s = {1 - (!(p1[x] < p2[x]) * 2), 1 - (!(p1[y] < p2[y]) * 2)};
  int err = d[x] - d[y];
  while (1) {
    draw_point(surface, p1, ci);
    if (p1[x] == p2[x] && p1[y] == p2[y]) break;
    int e2 = 2 * err;
    if (e2 > -d[y]) {
      err -= d[y];
      p1[x] += s[x];
    }
    if (e2 < d[x]) {
      err += d[x];
      p1[y] += s[y];
    }
  }
}

void draw_lines(SDL_Surface* surface, vec3* coordinates, int num_steps, char ci) {
  for (int i = 0; i < num_steps - 1 ; i++) {
    draw_line(surface, coordinates[i], coordinates[i + 1], ci);
  }
}

void draw_circle(SDL_Surface* surface, int radius, vec3 coordinates, char ci) {
    for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      vec2i d = {radius - w, radius - h};
      if ((d[x] * d[x] + d[y] * d[y]) <= (radius * radius)) {
        vec2i p = {coordinates[x] + d[x], coordinates[y] + d[y]};
        draw_point(surface, p, ci);
      }
    }
  }
}

void worldtod(vec3 coord, double zoom, int screen_radius) {
  vec3multd(coord, screen_radius * zoom);
  vec3sumd(coord, screen_radius);
}

void fixframe(vec3 coord, vec3 fixed_coord) {
  vec3 fixed = {fixed_coord[x], fixed_coord[y], fixed_coord[z]};
  vec3subv(coord, fixed);
}

int inscreen(int x, int y, int size) {
  return x > 0 && y > 0 && x < size && y < size;
}