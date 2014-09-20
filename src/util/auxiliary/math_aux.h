/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef MATH_AUX_H_
#define MATH_AUX_H_

#include "util/wrapper/glm_wrap.h"

namespace math_aux {
inline int sign(int value) {
  return (value > 0) - (value < 0);
}
inline float sign(float value) {
  return static_cast<float>((value > 0.0f) - (value < 0.0f));
}
inline double sign(double value) {
  return static_cast<double>((value > 0.0) - (value < 0.0));
}

inline float saturate(float value) {
  return (value > 1.0f) ? 1.0f : (value < 0.0f) ? 0.0f : value;
}
inline double saturate(double value) {
  return (value > 1.0) ? 1.0 : (value < 0.0) ? 0.0 : value;
}

inline bool is_fequal(float lvalue, float rvalue) {
  return glm::epsilonEqual(lvalue, rvalue, glm::epsilon<float>());
}
inline bool is_fzero(float value) {
  return is_fequal(value, 0.0f);
}

inline float square(float value) {
  return pow(value, 2);
}
inline double square(double value) {
  return pow(value, 2);
}
inline float cubic(float value) {
  return pow(value, 3);
}
inline double cubic(double value) {
  return pow(value, 3);
}
inline float twice(float value) {
  return value * 2.0f;
}
inline double twice(double value) {
  return value * 2.0;
}
inline float treble(float value) {
  return value * 3.0f;
}
inline double treble(double value) {
  return value * 3.0;
}
inline float half(float value) {
  return value * 0.5f;
}
inline double half(double value) {
  return value * 0.5;
}
inline float quater(float value) {
  return value * 0.25f;
}
inline double quater(double value) {
  return value * 0.25;
}
}

#endif /* MATH_AUX_H_ */
