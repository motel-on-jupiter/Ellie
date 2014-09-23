/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "camera/Camera.h"

Camera::Camera(const glm::vec3& pos, const glm::vec3& at, const glm::vec3& up)
    : default_pos_(pos),
      default_at_(at),
      default_up_(up),
      pos_(pos),
      at_(at),
      up_(glm::normalize(up)) {
}

Camera::~Camera() {
}

