#include <rebound.h>
#include "sim.h"

typedef struct reb_simulation reb_simulation;

void heartbeat(reb_simulation* r);
void add_particles(reb_simulation* r, celestials_settings* cs);

int HEARTBEAT_MAX_STEPS;
int HEARTBEAT_STEP_INTERVAL;
celestial* HEARTBEAT_C;

void simulate(settings* s, celestials_settings* cs, int pre_sim) {
  HEARTBEAT_MAX_STEPS = s->max_steps;
  HEARTBEAT_STEP_INTERVAL = s->step_interval;
  HEARTBEAT_C = cs->celestials;

  reb_simulation* r = reb_create_simulation();
  if (!pre_sim) r->heartbeat = heartbeat;

  add_particles(r, cs);

  reb_integrate(r, s->sim_length);

  if (pre_sim) {
    s->max_steps = calculate_num_steps(r->steps_done, s->step_interval);
  }

  s->num_steps = calculate_num_steps(r->steps_done, s->step_interval);
  s->scale = cs->celestials[cs->reference_body].initial_orbit->a;

  printw("steps-done: %llu\nnum-steps: %i\nmax-steps: %i\nstep-interval: %i\n", r->steps_done, s->num_steps, s->max_steps, s->step_interval);
}

void heartbeat(reb_simulation* r) {
  if (r->steps_done < HEARTBEAT_MAX_STEPS * HEARTBEAT_STEP_INTERVAL) {
    if (!(r->steps_done % HEARTBEAT_STEP_INTERVAL)) {
      for (int i = 0; i < r->N; i++) {
        HEARTBEAT_C[i].coordinates[r->steps_done / HEARTBEAT_STEP_INTERVAL][x] = r->particles[i].x;
        HEARTBEAT_C[i].coordinates[r->steps_done / HEARTBEAT_STEP_INTERVAL][y] = r->particles[i].y;
        HEARTBEAT_C[i].coordinates[r->steps_done / HEARTBEAT_STEP_INTERVAL][z] = r->particles[i].z;
      }
    }
  } else {
    reb_stop(r);
  }
}

int calculate_num_steps(int steps_done, int step_interval) {
  if (!(steps_done % step_interval)) return steps_done / step_interval;
  return (steps_done + step_interval - (steps_done % step_interval)) / step_interval;
}

void add_particles(reb_simulation* r, celestials_settings* cs) {
  celestial* c = cs->celestials;
  double scale = c[cs->reference_body].initial_orbit->a;
  double mass_scale = c[cs->center_body].mass;
  double time_scale = orbital_period(mass_scale, c[cs->reference_body].mass, scale) / (2 * PI);

  for (int i = 0; i < cs->num_celestials; i++) {
    double m = c[i].mass / mass_scale;
    if (c[i].initial_orbit == NULL) {
      double px = c[i].initial_coordinates[x] / scale; double py = c[i].initial_coordinates[y] / scale; double pz = c[i].initial_coordinates[z] / scale;
      double vx = c[i].initial_velocity[x] * (time_scale / scale); double vy = c[i].initial_velocity[y] * (time_scale / scale); double vz = c[i].initial_velocity[z] * (time_scale / scale);
      reb_add_fmt(r, "m x y z vx vy vz", m, px, py, pz, vx, vy, vz);
    } else {
      double a = c[i].initial_orbit->a / scale;
      double e = c[i].initial_orbit->e;
      double inc = c[i].initial_orbit->i;
      double lan = c[i].initial_orbit->lan;
      double ap = c[i].initial_orbit->ap;
      double ta = c[i].initial_orbit->ta;
      reb_add_fmt(r, "m a e inc Omega omega f", m, a, e, inc, lan, ap, ta);
    }
  }
}
