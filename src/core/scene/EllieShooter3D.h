/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTER_3D_H_
#define ELLIE_SHOOTER_3D_H_

#include <vector>
#include "core/stage/GridStage3D.h"
#include "core/EllieGame.h"

class EllieShooter3D : public EllieBaseGameScene {
 public:
  EllieShooter3D();
  virtual ~EllieShooter3D();

  virtual int Initialize();
  virtual void Finalize();
  virtual void Update(float elapsed_time);
  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(SDL_Keycode key);
  virtual void OnKeyUp(SDL_Keycode key);

 private:
  GridStage3D stage_;
};

#endif /* ELLIE_SHOOTER_3D_H_ */
