/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ELLIE_GAME_H_
#define ELLIE_GAME_H_

#include <vector>
#include <SDL_ttf.h>

class EllieGameSceneRendererInterface {
 public:
  EllieGameSceneRendererInterface() {
  }
  virtual ~EllieGameSceneRendererInterface() {
  }

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;

  virtual void Begin(const glm::vec2 &window_size) = 0;
  virtual void End() = 0;
};

class EllieGameSceneInterface {
 public:
  EllieGameSceneInterface() {
  }
  virtual ~EllieGameSceneInterface() {
  }

  virtual int Initialize(const glm::vec2 &window_size) = 0;
  virtual void Finalize() = 0;
  virtual void Update(float elapsed_time, const glm::vec2 &window_size) = 0;
  virtual void Draw(const glm::vec2 &window_size) = 0;
  virtual int OnMouseButtonDown(unsigned char button,
                                const glm::vec2 &cursor_pos) = 0;
};

class EllieGame {
 public:
  EllieGame();
  ~EllieGame();

  int Initialize();
  void Finalize();
  void Update(float elapsed_time, const glm::vec2 &window_size);
  void Draw(const glm::vec2 &window_size);
  int OnKeyboardDown(SDL_Keycode key, const glm::vec2 &window_size);
  int OnMouseButtonDown(unsigned char button, int x, int y,
                        const glm::vec2 &window_size);

 private:
  std::vector<EllieGameSceneInterface *> scenes_;
  EllieGameSceneInterface *active_scene_;
  TTF_Font *font_;
};

#endif /* ELLIE_GAME_H_ */
