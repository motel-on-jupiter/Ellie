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
  static const glm::vec3 kSize;
  static const unsigned int kPatience;
  static const float kMoveSpeed;
  static const float kTurnSpeed;

  Zombie(const glm::vec3 &pos, const glm::quat &rot);
  virtual ~Zombie();

  virtual bool Initialize();
  void Update(const glm::vec3 &player_pos, float fps);

  void TakeDamage();
  bool IsDead() const {
    return total_damage_ > kPatience;
  }

 private:
  btBoxShape *colli_shape_;
  unsigned int total_damage_;
};

#endif /* ZOMBIE_H_ */
