#include "universe.h"

double orbital_period(double cm, double m, double a) {
  return sqrt(((4*PI2)/(G*(cm + m)))*pow(a, 3));
}