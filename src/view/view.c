#include "view.h"

vec3 colors[] = {
  {0, 0, 255},
  {0, 255, 0},
  {255, 0, 0},
  {0, 255, 255},
  {255, 0, 255},
  {255, 255, 0},
  {255, 255, 255},
};

void render(settings s, celestials_settings cs) {
  int screen_radius = s.screen_size / 2;
  celestial* c = cs.celestials;

  for (int i = 0; i < s.screen_size; i++) {
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
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Event event;


  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for (int i = 0; i < cs.num_celestials; i++) {
    draw_lines(renderer, c[i].coordinates, s.num_steps, i, screen_radius);
    draw_circle(renderer, (c[i].radius / s.scale) * screen_radius * s.zoom, c[i].coordinates[s.num_steps - 1], i, screen_radius);
  }

  SDL_RenderPresent(renderer);

  int quit = 0;
  while (!quit) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void draw_circle(SDL_Renderer *renderer, int radius, vec3 coordinates, int ci, int screen_radius) {
  SDL_SetRenderDrawColor(renderer, colors[ci][x], colors[ci][y], colors[ci][z], 255);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        if (inscreen(coordinates[x] + dx, coordinates[y] + dy, screen_radius * 2)) {
          SDL_RenderDrawPoint(renderer, coordinates[x] + dx, coordinates[y] + dy);
        }
      }
    }
  }
}

void draw_lines(SDL_Renderer *renderer, vec3* coordinates, int num_steps, int ci, int screen_radius) {
  SDL_SetRenderDrawColor(renderer, colors[ci][x], colors[ci][y], colors[ci][z], 255);
  for (int i = 0; i < num_steps - 1; i++) {
    if (inscreen(coordinates[i][x], coordinates[i][y], screen_radius * 2)) {
      SDL_RenderDrawLine(renderer, coordinates[i][x], coordinates[i][y], coordinates[i + 1][x], coordinates[i + 1] [y]);
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
  return x >= 0 && y >= 0 && x <= size && y <= size;
}