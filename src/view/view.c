#include "view.h"

void render(settings s, celestials_settings cs) {
  int screen_radius = s.screen_size / 2;
  int section_radius = screen_radius / 2;
  celestial* c = cs.celestials;

  for (int i = 0; i < s.num_steps; i++) {
    for (int j = 0; j < cs.num_celestials; j++) {
      worldtod(c[j].coordinates[i], s.zoom, section_radius);
    }
    vec3 fixed_frame = {c[cs.fixed_body].coordinates[i][x], c[cs.fixed_body].coordinates[i][y], c[cs.fixed_body].coordinates[i][z]};
    vec3subd(fixed_frame, section_radius);
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
  colors[1].r = 255; colors[1].g = 255; colors[1].b = 255;
  colors[2].r = 0; colors[2].g = 0; colors[2].b = 255;
  colors[3].r = 0; colors[3].g = 255; colors[3].b = 0;
  colors[4].r = 255; colors[4].g = 0; colors[4].b = 0;
  SDL_SetPaletteColors(surface->format->palette, colors, 0, 5);

  SDL_FillRect(surface, NULL, 0);
  vec2i sections[3] = {
    {0, 0},
    {screen_radius, 0},
    {screen_radius, screen_radius},
  };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < cs.num_celestials; j++) {
      draw_circle(surface, (c[j].radius / s.scale) * section_radius * s.zoom, c[j].coordinates[s.num_steps - 1], (char)j + 2, 2-i, (vec2i){screen_radius, screen_radius}, sections[i]);
      draw_lines(surface, c[j].coordinates, s.num_steps, (char)j + 2, 2-i, (vec2i){screen_radius, screen_radius}, sections[i]);
    }
  }
  draw_grid(surface);

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

void draw_point(SDL_Surface* surface, vec2i p, char color_i) {
  if (inscreen(p, (vec2i){surface->w, surface->w}, (vec2i){0, 0})) {
    char* pixel = (char*)surface->pixels + p[y] * surface->pitch + p[x];
    *pixel = color_i;
  }
}

void draw_line(SDL_Surface* surface, vec2i p1, vec2i p2, char color_i, vec2i max, vec2i section) {
  vec2i d = {abs((p2[x] - p1[x])), abs((p2[y] - p1[y]))};
  vec2i s = {1 - (!(p1[x] < p2[x]) * 2), 1 - (!(p1[y] < p2[y]) * 2)};
  int err = d[x] - d[y];
  while (1) {
    if (inscreen(p1, max, (vec2i){0, 0})) draw_point(surface, (vec2i){p1[x] + section[x], p1[y] + section[y]}, color_i);
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

void draw_grid(SDL_Surface* surface) {
  vec2i vml = {0, surface->w / 2}; vec2i vmr = {surface->w, surface->w / 2};
  vec2i hmu = {surface->w / 2, 0}; vec2i hmb = {surface->w / 2, surface->w};
  draw_line(surface, vml, vmr, 1, (vec2i){surface->w, surface->w}, (vec2i){0, 0});
  draw_line(surface, hmu, hmb, 1, (vec2i){surface->w, surface->w}, (vec2i){0, 0});
}

void draw_lines(SDL_Surface* surface, vec3* coordinates, int num_steps, char color_i, char camera_axis, vec2i max, vec2i section) {
  for (int i = 0; i < num_steps - 1 ; i++) {
    vec2i p1 = {(int)coordinates[i][!camera_axis], (int)coordinates[i][(camera_axis != 2) + 1]};
    vec2i p2 = {(int)coordinates[i + 1][!camera_axis], (int)coordinates[i + 1][(camera_axis != 2) + 1]};
    draw_line(surface, p1, p2, color_i, max, section);
  }
}

void draw_circle(SDL_Surface* surface, int radius, vec3 coordinates, char color_i, char camera_axis, vec2i max, vec2i section) {
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      vec2i d = {radius - w, radius - h};
      if ((d[x] * d[x] + d[y] * d[y]) <= (radius * radius)) {
        vec2i p = {coordinates[!camera_axis] + d[x], coordinates[(camera_axis != 2) + 1] + d[y]};
        if (inscreen(p, max, (vec2i){0, 0})) {
          draw_point(surface, (vec2i){p[x] + section[x], p[y] + section[y]}, color_i);
        }
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

int inscreen(vec2i p, vec2i max, vec2i min) {
  return p[x] >= min[x] && p[x] < max[x] && p[y] >= min[y] && p[y] < max[y];
}