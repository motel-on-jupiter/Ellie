/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"

class Zombie : public CubicEntity, public EntityCubeDraw,
    public CubicEntityPhysics {
 public:
  static const unsigned int kHP;

  Zombie(const glm::vec3 &pos, const glm::quat &rot);
  virtual ~Zombie();

  virtual bool Initialize();

  void TakeDamage() {
    ++damage_;
  }
  bool IsDead() const {
    return damage_ >= hp_;
  }

 private:
  unsigned int damage_;
  unsigned int hp_;
};

#endif /* ZOMBIE_H_ */
