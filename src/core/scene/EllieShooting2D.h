/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTING_2D_H_
#define ELLIE_SHOOTING_2D_H_

#include <vector>
#include "core/actor/F22Fighter.h"
#include "core/actor/UFOFighter.h"
#include "core/EllieGame.h"

class EllieShooting2DStage {
 public:
  EllieShooting2DStage();
  ~EllieShooting2DStage();

  void Draw(const glm::vec2 &window_size);

 private:
  static const size_t kNumXMappingStars;
  static const size_t kNumYMappingStars;
  static const int kRatioMappingStars;

  std::vector<std::vector<bool>> star_map_;
};

class EllieShooting2DIngame : public EllieBaseGameScene {
 public:
  EllieShooting2DIngame();
  virtual ~EllieShooting2DIngame();

  virtual int Initialize();
  virtual void Finalize();
  virtual void Update(float elapsed_time);
  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(SDL_Keycode key);
  virtual void OnKeyUp(SDL_Keycode key);

 private:
  static const float kShotInterval;
  static const glm::vec2 kBulletVelocity;

  virtual void DirectEnemies(float elapsed_time);

  F22Fighter f22_;
  FighterBullet bullets_[100];
  UFOFighter ufos_[100];
  void *ccrParam_;
  float time_;
  int ufo_idx_;
  bool scene_pausing_;
  bool moving_[4];
  bool shooting_;
  float shot_interval_;
};

class EllieShooting2D : public EllieBaseGameScene {
 public:
  EllieShooting2D();
  virtual ~EllieShooting2D();

  virtual int Initialize();
  virtual void Finalize();
  virtual void Update(float elapsed_time);
  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(SDL_Keycode key);
  virtual void OnKeyUp(SDL_Keycode key);

 private:
  EllieShooting2DStage stage_;
  std::vector<EllieBaseGameScene *> sub_scenes_;
  EllieBaseGameScene *current_scene_;
};

#endif /* ELLIE_SHOOTING_2D_H_ */
