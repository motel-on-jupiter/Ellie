/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "camera/FirstPersonCameraController.h"
#include <glm/gtx/rotate_vector.hpp>
#include "auxiliary/csyntax_aux.h"

FirstPersonCameraController::FirstPersonCameraController(Camera &camera,
                                                         float translate_speed,
                                                         float rotate_speed)
    : BaseCameraController(camera),
      translate_speed_(translate_speed),
      rotate_speed_(rotate_speed),
      pressing_key_() {
}

FirstPersonCameraController::~FirstPersonCameraController() {
}

void FirstPersonCameraController::Update(float elapsed_time) {
  glm::vec3 forward = camera().at() - camera().pos();
  forward.y = 0.0f;
  if (glm::epsilon<float>() > glm::length(forward)) {
    forward = glm::vec3(1.0f, 0.0f, 0.0f);
  }
  forward = glm::normalize(forward);
  glm::vec3 right = glm::rotateY(forward, glm::pi<float>() * -0.5f);

  auto it = pressing_key_.begin();
  for (; pressing_key_.end() != it; ++it) {
    float translation = translate_speed_ * elapsed_time;
    if ('w' == *it) {
      camera().set_pos(camera().pos() + forward * translation);
      camera().set_at(camera().at() + forward * translation);
    } else if ('s' == *it) {
      camera().set_pos(camera().pos() - forward * translation);
      camera().set_at(camera().at() - forward * translation);
    } else if ('d' == *it) {
      camera().set_pos(camera().pos() + right * translation);
      camera().set_at(camera().at() + right * translation);
    } else if ('a' == *it) {
      camera().set_pos(camera().pos() - right * translation);
      camera().set_at(camera().at() - right * translation);
    }
  }
}

void FirstPersonCameraController::OnKeyDown(const SDL_KeyboardEvent &keyboard) {
  pressing_key_.insert(keyboard.keysym.sym);
}

void FirstPersonCameraController::OnKeyUp(const SDL_KeyboardEvent &keyboard) {
  auto it = pressing_key_.find(keyboard.keysym.sym);
  if (pressing_key_.end() != it) {
    pressing_key_.erase(it);
  }
}

void FirstPersonCameraController::OnMouseMotion(
    const SDL_MouseMotionEvent &motion) {
  float deltaX = static_cast<float>(motion.xrel);
  float deltaY = static_cast<float>(motion.yrel);

  glm::vec3 forward = camera().at() - camera().pos();
  forward.y = 0.0f;
  if (glm::epsilon<float>() > glm::length(forward)) {
    forward = glm::vec3(1.0f, 0.0f, 0.0f);
  } else {
    forward = glm::normalize(forward);
  }
  glm::vec3 right = glm::rotateY(forward, glm::pi<float>() * -0.5f);

  glm::vec3 local = camera().at() - camera().pos();
  glm::vec3 rotated = glm::rotate(local, deltaY * rotate_speed_ * -1.0f, right);
  float atan = glm::atan(rotated.y,
                         glm::length(glm::vec2(rotated.x, rotated.z)));
  if (abs(atan) > 0.25f * glm::pi<float>()) {
    rotated = local;
  }
  rotated = glm::rotateY(rotated, deltaX * rotate_speed_ * -1.0f);
  camera().set_at(camera().pos() + rotated);
  camera().set_up(glm::rotateY(camera().up(), deltaY * rotate_speed_ * -1.0f));
}
