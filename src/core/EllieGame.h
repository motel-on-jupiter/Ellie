/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ELLIE_GAME_H_
#define ELLIE_GAME_H_

#include <vector>
#include <SDL_ttf.h>

class EllieBaseGameScene {
 public:
  EllieBaseGameScene(const char *name)
      : name_(name),
        finished_(true),
        scene_time_(0.0f) {
  }
  virtual ~EllieBaseGameScene() {
  }

  int Initialize();
  void Finalize();
  void Update(float elapsed_time);

  virtual void Draw(const glm::vec2 &window_size) = 0;
  virtual void OnKeyDown(const SDL_KeyboardEvent &key) = 0;
  virtual void OnKeyUp(const SDL_KeyboardEvent &key) = 0;
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button) = 0;
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion) = 0;

  const std::string &name() const {
    return name_;
  }
  bool finished() const {
    return finished_;
  }
  float scene_time() const {
    return scene_time_;
  }

 protected:
  virtual int OnInitial() = 0;
  virtual void OnFinal() = 0;
  virtual void OnUpdate(float elapsed_time) = 0;

  void set_finished(bool finished) {
    finished_ = finished;
  }

 private:
  std::string name_;
  bool finished_;
  float scene_time_;
};

class EllieGame {
 public:
  EllieGame();
  ~EllieGame();

  int Initialize();
  void Finalize();
  void Update(float elapsed_time);
  void Draw(const glm::vec2 &window_size);
  int OnKeyDown(const SDL_KeyboardEvent &keyboard);
  void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  void OnMouseMotion(const SDL_MouseMotionEvent &motion);

  bool ongoing() const {
    return ongoing_;
  }

 private:
  std::vector<EllieBaseGameScene *> scenes_;
  EllieBaseGameScene *current_scene_;
  TTF_Font *font_;
  unsigned int cursor_;
  bool ongoing_;
};

#endif /* ELLIE_GAME_H_ */
