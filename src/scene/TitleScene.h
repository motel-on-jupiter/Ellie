/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "scene/BaseScene.h"

class TitleScene : public BaseScene {
 public:
  TitleScene(const char *name);
  virtual ~TitleScene();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard);
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnUpdate(float elapsed_time);
};

#endif /* TITLE_SCENE_H_ */
