#include "vector.h"

void vec3cpy(vec3 v1, vec3 v2) {
  v1[x] = v2[x]; v1[y] = v2[y]; v1[z] = v2[z];
}

void vec3set(vec3 v1, double x1, double y1, double z1) {
  v1[x] = x1; v1[y] = y1; v1[z] = z1;
}

void vec3sumv(vec3 v1, vec3 v2) {
  v1[x] = v1[x] + v2[x];
  v1[y] = v1[y] + v2[y];
  v1[z] = v1[z] + v2[z];
}

void vec3subv(vec3 v1, vec3 v2) {
  v1[x] = v1[x] - v2[x];
  v1[y] = v1[y] - v2[y];
  v1[z] = v1[z] - v2[z];
}

void vec3multv(vec3 v1, vec3 v2) {
  v1[x] = v1[x] * v2[x];
  v1[y] = v1[y] * v2[y];
  v1[z] = v1[z] * v2[z];
}

void vec3divv(vec3 v1, vec3 v2) {
  v1[x] = v1[x] / v2[x];
  v1[y] = v1[y] / v2[y];
  v1[z] = v1[z] / v2[z];
}

void vec3sumd(vec3 v, double d) {
  v[x] = v[x] + d;
  v[y] = v[y] + d;
  v[z] = v[z] + d;
}

void vec3subd(vec3 v, double d) {
  v[x] = v[x] - d;
  v[y] = v[y] - d;
  v[z] = v[z] - d;
}

void vec3multd(vec3 v, double d) {
  v[x] = v[x] * d;
  v[y] = v[y] * d;
  v[z] = v[z] * d;
}

void vec3divd(vec3 v, double d) {
  v[x] = v[x] / d;
  v[y] = v[y] / d;
  v[z] = v[z] / d;
}
