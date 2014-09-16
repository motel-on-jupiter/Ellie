/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include <boost/noncopyable.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
 public:
  Camera(const glm::vec3& pos, const glm::vec3& at, const glm::vec3& up);
  virtual ~Camera();

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

  const glm::mat4 &BuildLookAt() const {
    return glm::lookAt(pos_, at_, up_);
  }

 protected:
  glm::vec3 pos_;
  glm::vec3 at_;
  glm::vec3 up_;
};

class BaseCameraController : public boost::noncopyable {
public:
  BaseCameraController(Camera &camera) : camera_(camera) {}
  virtual ~BaseCameraController() {}

  virtual void Update() = 0;
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard) = 0;
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard) = 0;
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion) = 0;

protected:
  Camera &camera() { return camera_; }

private:
  Camera &camera_;
};

#endif /* CAMERA_H_ */
