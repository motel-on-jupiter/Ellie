/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include <boost/noncopyable.hpp>
#include "util/auxiliary/glm_aux.h"
#include "util/wrapper/glm_wrap.h"

class Camera {
 public:
  Camera(const glm::vec3& pos, const glm::vec3& at, const glm::vec3& up);
  virtual ~Camera();

  void Reset() {
    set_pos(default_pos_);
    set_at(default_at_);
    set_up(default_up_);
  }

  const glm::vec3 &pos() const {
    return pos_;
  }
  const glm::vec3 &at() const {
    return at_;
  }
  const glm::vec3 &up() const {
    return up_;
  }

  void set_pos(const glm::vec3 &pos) {
    pos_ = pos;
  }
  void set_at(const glm::vec3 &at) {
    at_ = at;
  }
  void set_up(const glm::vec3 &up) {
    up_ = up;
  }

  glm::mat4 BuildViewMatrix() const {
    return glm::lookAt(pos_, at_, up_);
  }
  glm::vec3 BuildForwardDir() const {
    glm::vec3 forward = at_ - pos_;
    if (glm::length2(forward) < glm_aux::epsilon()) {
      return glm::vec3(0.0f, 0.0f, 1.0f);
    }
    return glm::normalize(forward);
  }
  glm::quat BuildRotation() const {
    return glm_aux::angleBetweenVectors(glm_aux::z_dir(), BuildForwardDir());
  }

 protected:
  glm::vec3 default_pos_;
  glm::vec3 default_at_;
  glm::vec3 default_up_;
  glm::vec3 pos_;
  glm::vec3 at_;
  glm::vec3 up_;
};

class BaseCameraController : public boost::noncopyable {
 public:
  BaseCameraController(Camera &camera)
      : camera_(camera) {
  }
  virtual ~BaseCameraController() {
  }

  virtual void Update(float elapsed_time) = 0;
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard) = 0;
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard) = 0;
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion) = 0;

 protected:
  Camera &camera() {
    return camera_;
  }

 private:
  Camera &camera_;
};

#endif /* CAMERA_H_ */
