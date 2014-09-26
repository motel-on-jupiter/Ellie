/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ELLIE_GAME_H_
#define ELLIE_GAME_H_

#include <vector>
#include <SDL_ttf.h>

class BaseScene;

class EllieGame {
 public:
  EllieGame();
  ~EllieGame();

  int Initialize();
  void Finalize();
  void Step(float elapsed_time);
  void Draw(const glm::vec2 &window_size);
  int OnKeyDown(const SDL_KeyboardEvent &keyboard);
  void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  void OnMouseMotion(const SDL_MouseMotionEvent &motion);

  bool on_going() const {
    return on_going_;
  }

 private:
  std::vector<BaseScene *> scenes_;
  BaseScene *current_scene_;
  TTF_Font *font_;
  unsigned int cursor_;
  bool on_going_;
};

#endif /* ELLIE_GAME_H_ */
