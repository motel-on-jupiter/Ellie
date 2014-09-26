/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTING_2D_H_
#define ELLIE_SHOOTING_2D_H_

#include <map>
#include <string>
#include "core/actor/F22Fighter.h"
#include "core/actor/UFOFighter.h"
#include "core/EllieGame.h"
#include "scene/BaseScene.h"
#include "scene/GraphDrivenScene.h"
#include "scene/SceneGraph.h"

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

class EllieShooting2DIngame : public BaseScene {
 public:
  EllieShooting2DIngame();
  virtual ~EllieShooting2DIngame();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard);
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnStep(float elapsed_time);

 private:
  static const float kShotInterval;
  static const glm::vec2 kBulletVelocity;

  virtual void DirectEnemies(float elapsed_time);

  F22Fighter f22_;
  FighterBullet bullets_[100];
  UFOFighter ufos_[100];
  void *ccr_param_;
  float time_;
  int ufo_idx_;
  bool scene_pausing_;
  bool moving_[4];
  bool shooting_;
  float shot_interval_;
};

class EllieShooting2D : public GraphDrivenScene {
 public:
  EllieShooting2D();
  virtual ~EllieShooting2D();

  virtual void Draw(const glm::vec2 &window_size);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();

 private:
  EllieShooting2DStage stage_;
  std::vector<BaseScene *> scene_pool_;
  SceneGraph scene_graph_;
};

#endif /* ELLIE_SHOOTING_2D_H_ */
