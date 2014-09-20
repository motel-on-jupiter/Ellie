/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef GLM_AUX_H_
#define GLM_AUX_H_

#include "util/wrapper/glm_wrap.h"
#include "util/wrapper/bullet_wrap.h"

namespace glm_aux {
inline float normalize_angle(float angle) {
  while (angle > glm::pi<float>()) {
    angle -= glm::pi<float>() * 2.0f;
  }
  while (angle < glm::pi<float>() * -1.0f) {
    angle += glm::pi<float>() * 2.0f;
  }
  return angle;
}

inline btVector3 castToBt(const glm::vec3 &glm_vec) {
  return btVector3(glm_vec.x, glm_vec.y, glm_vec.z);
}
inline btQuaternion castToBt(const glm::quat &glm_quat) {
  return btQuaternion(glm_quat.x, glm_quat.y, glm_quat.z, glm_quat.w);
}
}

#endif /* GLM_AUX_H_ */
