/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"

class Zombie : public CubicEntity, public EntityCubeDraw {
 public:
  Zombie();
  virtual ~Zombie();

  bool Initialize();
  void Finalize();

  btRigidBody *bt_body() {
    return bt_body_;
  }

 private:
  void CleanObjects();

  btCollisionShape *bt_shape_;
  btDefaultMotionState *bt_motion_;
  btRigidBody* bt_body_;
};

#endif /* ZOMBIE_H_ */
