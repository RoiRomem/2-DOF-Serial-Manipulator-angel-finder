#pragma once
#include <float.h>
#include <math.h>

typedef struct {
  float radians;
} angle;

static inline angle angle_rad(float r) { return (angle){r}; }

static inline angle angle_deg(float d) {
  return (angle){d * (float)M_PI / 180.0f};
}

static inline float angle_to_rad(angle a) { return a.radians; }

static inline float angle_to_deg(angle a) {
  return a.radians * 180.0f / (float)M_PI;
}

static inline angle angle_add(angle a, angle b) {
  return (angle){a.radians + b.radians};
}

static inline angle angle_sub(angle a, angle b) {
  return (angle){a.radians - b.radians};
}

static inline angle angle_mul(angle a, float s) {
  return (angle){a.radians * s};
}

static inline angle angle_div(angle a, float s) {
  return (angle){a.radians / s};
}

static inline angle angle_normalize(angle a) {
  float two_pi = 2.0f * (float)M_PI;
  a.radians = fmodf(a.radians, two_pi);
  if (a.radians < 0)
    a.radians += two_pi;
  return a;
}

static inline float angle_sin(angle a) { return sinf(a.radians); }

static inline float angle_cos(angle a) { return cosf(a.radians); }

static inline float angle_tan(angle a) { return tanf(a.radians); }

static inline angle angle_asin(float x) { return (angle){asinf(x)}; }

static inline angle angle_acos(float x) { return (angle){acosf(x)}; }

static inline angle angle_atan(float x) { return (angle){atanf(x)}; }

static inline angle angle_atan2(float y, float x) {
  return (angle){atan2f(y, x)};
}

static inline float angle_sin_deg(float d) {
  return sinf(d * (float)M_PI / 180.0f);
}

static inline float angle_cos_deg(float d) {
  return cosf(d * (float)M_PI / 180.0f);
}

static inline float angle_tan_deg(float d) {
  return tanf(d * (float)M_PI / 180.0f);
}

static inline float cosine_law_side(float a, float b, angle C) {
  return sqrtf(a * a + b * b - 2.0f * a * b * cosf(C.radians));
}

static inline angle cosine_law_angle(float a, float b, float c) {
  float denom = 2.0f * a * b;

  if (fabsf(denom) < FLT_EPSILON) {
    return (angle){0};
  }

  float cosC = (a * a + b * b - c * c) / denom;

  cosC = fmaxf(-1.0f, fminf(1.0f, cosC));

  return (angle){acosf(cosC)};
}
