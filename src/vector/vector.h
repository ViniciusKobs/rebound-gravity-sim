#pragma once

typedef double vec3[3];
typedef int vec2i[2];
typedef int vec3i[3];
enum axis {x, y, z};

void vec3cpy(vec3 v1, vec3 v2);
void vec3set(vec3 v1, double x1, double y1, double z1);
void vec3sumv(vec3 v1, vec3 v2);
void vec3subv(vec3 v1, vec3 v2);
void vec3multv(vec3 v1, vec3 v2);
void vec3divv(vec3 v1, vec3 v2);
void vec3sumd(vec3 v1, double d);
void vec3subd(vec3 v1, double d);
void vec3multd(vec3 v1, double d);
void vec3divd(vec3 v1, double d);