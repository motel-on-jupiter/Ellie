/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTER_3D_H_
#define ELLIE_SHOOTER_3D_H_

#include <vector>
#include "core/actor/Zombie.h"
#include "core/stage/GridStage3D.h"
#include "core/EllieGame.h"

class EllieShooter3D : public EllieBaseGameScene {
 public:
  EllieShooter3D();
  virtual ~EllieShooter3D();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(SDL_Keycode key);
  virtual void OnKeyUp(SDL_Keycode key);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnUpdate(float elapsed_time);

 private:
  GridStage3D stage_;
  Zombie zombie_;
};

#endif /* ELLIE_SHOOTER_3D_H_ */
