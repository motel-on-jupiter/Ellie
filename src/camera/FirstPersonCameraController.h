/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef FIRSTPERSONCAMERA_H_
#define FIRSTPERSONCAMERA_H_

#include <set>
#include "camera/Camera.h"

class FirstPersonCameraController : public BaseCameraController {
 public:
  FirstPersonCameraController(Camera &camera, float translate_speed,
                              float rotate_speed);
  virtual ~FirstPersonCameraController();

  virtual void Update();
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard);
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 private:
  float translate_speed_;
  float rotate_speed_;
  std::set<SDL_Keycode> pressing_key_;
};

#endif /* FIRSTPERSONCAMERA_H_ */
