/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"

class Zombie : public CubicEntity, public EntityCubeDraw {
 public:
  static const unsigned int kHP;

  Zombie();
  virtual ~Zombie();

  bool Initialize();
  void Finalize();

  void TakeDamage() { ++damage_; }
  bool IsDead() const { return damage_ >= hp_; }

  btRigidBody *bt_body() {
    return bt_body_;
  }

 private:
  void CleanObjects();

  btCollisionShape *bt_shape_;
  btDefaultMotionState *bt_motion_;
  btRigidBody* bt_body_;
  unsigned int damage_;
  unsigned int hp_;
};

#endif /* ZOMBIE_H_ */
