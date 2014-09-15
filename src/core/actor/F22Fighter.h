/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef F22FIGHTER_H_
#define F22FIGHTER_H_

#include "entity/PlanarEntity.h"
#include "entity/PlanarEntityDraw.h"

class FighterBullet : public PlanarEntity, public EntityPointDraw {
 public:
  FighterBullet();
  virtual ~FighterBullet();

  virtual void Initialize(const glm::vec2 &pos, const glm::vec2 &vel);
  virtual void Update(float elapsed_time);
  virtual void Draw();
  int IsActive() const { return life_time_ > 0.0f; }

 private:
  glm::vec2 vel_;
  float life_time_;
};

class F22Fighter : public PlanarEntity, public EntityTriangleDraw {
 public:
  F22Fighter();
  virtual ~F22Fighter();

  virtual void Initialize(const glm::vec2 &pos, float rot);
  void MoveForward();
  void MoveBack();
  void MoveLeft();
  void MoveRight();
  glm::vec2 GetShotPos(bool left) const;
};

#endif /* F22FIGHTER_H_ */
