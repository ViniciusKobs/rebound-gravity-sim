#pragma once

#include "../vector/vector.h"

typedef struct {
  double a;
  double e;
  double i;
  double lan;
  double ap;
  double ta;
} orbit;

typedef struct {
  double mass;
  double radius;
  vec3 initial_coordinates;
  vec3 initial_velocity;
  orbit* initial_orbit;
  vec3* coordinates;
} celestial;
