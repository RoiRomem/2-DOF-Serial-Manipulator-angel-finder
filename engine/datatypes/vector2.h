#pragma once
#include <math.h>

typedef struct {
  float x;
  float y;
} vector2;

static inline vector2 vec2(float x, float y) { return (vector2){x, y}; }

static inline vector2 vec2_add(vector2 a, vector2 b) {
  return (vector2){a.x + b.x, a.y + b.y};
}

static inline vector2 vec2_sub(vector2 a, vector2 b) {
  return (vector2){a.x - b.x, a.y - b.y};
}

static inline vector2 vec2_mul(vector2 v, float s) {
  return (vector2){v.x * s, v.y * s};
}

static inline float vec2_dot(vector2 a, vector2 b) {
  return a.x * b.x + a.y * b.y;
}

static inline float vec2_length(vector2 v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

static inline vector2 vec2_normalize(vector2 v) {
  float len = vec2_length(v);
  if (len == 0)
    return v;
  return vec2_mul(v, 1.0f / len);
}
