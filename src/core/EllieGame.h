/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ELLIE_GAME_H_
#define ELLIE_GAME_H_

#include <vector>
#include <SDL_ttf.h>

class EllieGameSceneInterface {
 public:
  EllieGameSceneInterface() {
  }
  virtual ~EllieGameSceneInterface() {
  }

  virtual int Initialize() = 0;
  virtual void Finalize() = 0;
  virtual void Update(float elapsed_time) = 0;
  virtual void Draw(const glm::vec2 &window_size) = 0;
  virtual void OnKeyDown(SDL_Keycode key) = 0;
  virtual void OnKeyUp(SDL_Keycode key) = 0;
};

class EllieGame {
 public:
  EllieGame();
  ~EllieGame();

  int Initialize();
  void Finalize();
  void Update(float elapsed_time);
  void Draw(const glm::vec2 &window_size);
  int OnKeyDown(SDL_Keycode key);
  void OnKeyUp(SDL_Keycode key);

 private:
  std::vector<EllieGameSceneInterface *> scenes_;
  EllieGameSceneInterface *current_scene_;
  TTF_Font *font_;
};

#endif /* ELLIE_GAME_H_ */
