/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef GLM_AUX_H_
#define GLM_AUX_H_

#include "util/wrapper/glm_wrap.h"
#include "util/wrapper/bullet_wrap.h"

namespace glm_aux {
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER glm::detail::tvec3<
    T, P> zero() {
  return glm::detail::tvec3<T, P>(0, 0, 0);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER glm::detail::tvec3<
    T, P> unit() {
  return glm::detail::tvec3<T, P>(1, 1, 1);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER glm::detail::tvec3<
    T, P> x_dir() {
  return glm::detail::tvec3<T, P>(1, 0, 0);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER glm::detail::tvec3<
    T, P> y_dir() {
  return glm::detail::tvec3<T, P>(0, 1, 0);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER glm::detail::tvec3<
    T, P> z_dir() {
  return glm::detail::tvec3<T, P>(0, 0, 1);
}
template<typename T = float> GLM_FUNC_QUALIFIER T epsilon() {
  return glm::epsilon<T>();
}

template<typename T = float> GLM_FUNC_QUALIFIER T normalizeAngle(T angle) {
  while (angle > glm::pi<T>()) {
    angle -= glm::pi<T>() * T(2);
  }
  while (angle < glm::pi<T>() * T(-1)) {
    angle += glm::pi<T>() * T(2);
  }
  return angle;
}

template <typename T = float, glm::precision P = glm::defaultp>
GLM_FUNC_DECL glm::detail::tquat<T, P> angleAxisX(
  T const & angle) {
  return glm::angleAxis(angle, x_dir<T, P>());
}
template <typename T = float, glm::precision P = glm::defaultp>
GLM_FUNC_DECL glm::detail::tquat<T, P> angleAxisY(
  T const & angle) {
  return glm::angleAxis(angle, y_dir<T, P>());
}
template <typename T = float, glm::precision P = glm::defaultp>
GLM_FUNC_DECL glm::detail::tquat<T, P> angleAxisZ(
  T const & angle) {
  return glm::angleAxis(angle, z_dir<T, P>());
}

template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER btVector3 toBtVec3(
    glm::detail::tvec3<T, P> const & v) {
  return btVector3(v.x, v.y, v.z);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER btVector4 toBtVec4(
    glm::detail::tvec4<T, P> const & v) {
  return btVector4(v.x, v.y, v.z, v.w);
}
template<typename T = float, glm::precision P = glm::defaultp> GLM_FUNC_QUALIFIER btQuaternion toBtQuat(
    glm::detail::tquat<T, P> const & q) {
  return btQuaternion(q.x, q.y, q.z, q.w);
}
}

#endif /* GLM_AUX_H_ */
