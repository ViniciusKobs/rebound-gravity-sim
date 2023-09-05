#include <rebound.h>
#include "sim.h"
#include <curses.h>

typedef struct reb_simulation reb_simulation;

void heartbeat(reb_simulation* r);

int MAX_STEPS;
celestial* C;

void simulate(settings* s, celestials_settings* cs) {
  MAX_STEPS = s->max_steps;
  C = cs->celestials;

  reb_simulation* r = reb_create_simulation();
  r->heartbeat= heartbeat;

  double scale = C[cs->reference_body].initial_orbit->a;
  double mass_scale = C[cs->center_body].mass;
  double time_scale = orbital_period(mass_scale, C[cs->reference_body].mass, scale) / (2 * PI);

  for (int i = 0; i < cs->num_celestials; i++) {
    double m = C[i].mass / mass_scale;
    if (C[i].initial_orbit == NULL) {
      double px = C[i].initial_coordinates[x] / scale; double py = C[i].initial_coordinates[y] / scale; double pz = C[i].initial_coordinates[z] / scale;
      double vx = C[i].initial_velocity[x] * (time_scale / scale); double vy = C[i].initial_velocity[y] * (time_scale / scale); double vz = C[i].initial_velocity[z] * (time_scale / scale);
      reb_add_fmt(r, "m x y z vx vy xz", m, px, py, pz, vx, vy, vz);
    } else {
      double a = C[i].initial_orbit->a / scale;
      double e = C[i].initial_orbit->e;
      double inc = C[i].initial_orbit->i;
      double lan = C[i].initial_orbit->lan;
      double ap = C[i].initial_orbit->ap;
      double ta = C[i].initial_orbit->ta;
      reb_add_fmt(r, "m a e inc Omega omega f", m, a, e, inc, lan, ap, ta);
    }
  }

  reb_integrate(r, s->sim_length);

  s->num_steps = r->steps_done;
  s->scale = scale;
}

void heartbeat(reb_simulation* r) {
  if (r->steps_done >= MAX_STEPS - 1) {
    reb_stop(r);
  } else {
    for (int i = 0; i < r->N; i++) {
      C[i].coordinates[r->steps_done][x] = r->particles[i].x;
      C[i].coordinates[r->steps_done][y] = r->particles[i].y;
      C[i].coordinates[r->steps_done][z] = r->particles[i].z;
    }
  }

}
