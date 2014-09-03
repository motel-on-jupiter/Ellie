/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef F22FIGHTER_H_
#define F22FIGHTER_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class FighterBullet : public BaseEntity, public EntityPointDraw {
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

class F22Fighter : public BaseEntity, public EntityTriangleDraw {
 public:
  F22Fighter();
  virtual ~F22Fighter();

  virtual void Initialize(const glm::vec2 &pos, float rot);
  glm::vec2 GetShotPos(bool left) const;
};

#endif /* F22FIGHTER_H_ */
