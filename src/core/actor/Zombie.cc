/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/actor/Zombie.h"
#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"
#include "util/catalogue/color_sample.h"

const unsigned int Zombie::kHP = 3;

Zombie::Zombie(const glm::vec3 &pos, const glm::quat &rot)
    : CubicEntity(pos, rot, glm::vec3(1.0f, 1.75f, 0.3f)),
      EntityCubeDraw(*static_cast<CubicEntity *>(this), true,
                     GLMaterialColor(X11Color::to_fvec(X11Color::kTeal))),
      CubicEntityPhysics(*static_cast<CubicEntity *>(this)),
      damage_(0),
      hp_(kHP) {
}

Zombie::~Zombie() {
}

bool Zombie::Initialize() {
  if (!CubicEntityPhysics::Initialize()) {
    return false;
  }
  damage_ = 0;
  return true;
}
