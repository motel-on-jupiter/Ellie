/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/actor/Zombie.h"
#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "util/catalogue/color_sample.h"

Zombie::Zombie()
    : CubicEntity(glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.75f, 0.3f)),
      EntityCubeDraw(*this, true, GLMaterialColor(X11Color::to_fvec(X11Color::kTeal))) {
}

Zombie::~Zombie() {
}

