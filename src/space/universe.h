#pragma once

#include <math.h>
#include "../vector/vector.h"

#define PI 3.141592653589793
#define PI2 9.869604401089358
#define G 6.6743E-11

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


double orbital_period(double cm, double m, double a);