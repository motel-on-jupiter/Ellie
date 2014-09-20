/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/actor/Zombie.h"
#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "util/auxiliary/glm_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/logging/Logger.h"

Zombie::Zombie()
    : CubicEntity(glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.75f, 0.3f)),
      EntityCubeDraw(*this, true,
                     GLMaterialColor(X11Color::to_fvec(X11Color::kTeal))),
      bt_shape_(nullptr),
      bt_motion_(nullptr),
      bt_body_(nullptr) {
}

Zombie::~Zombie() {
  delete bt_body_;
  delete bt_motion_;
  delete bt_shape_;
}

bool Zombie::Initialize() {
  bt_shape_ = new btBoxShape(glm_aux::castToBt(scale() * 0.5f));
  if (bt_shape_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet collsion shape object");
    return false;
  }
  glm::vec3 motion_pos = entity().pos()
      + glm::vec3(0.0f, entity().scale().y * 0.5f, 0.0f);
  bt_motion_ = new btDefaultMotionState(
      btTransform(glm_aux::castToBt(rot()), glm_aux::castToBt(motion_pos)));
  if (bt_motion_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet motion state object");
    CleanObjects();
    return false;
  }
  bt_body_ = new btRigidBody(
      btRigidBody::btRigidBodyConstructionInfo(1, bt_motion_, bt_shape_));
  if (bt_body_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet rigid body object");
    CleanObjects();
    return false;
  }
  return true;
}

void Zombie::Finalize() {
  CleanObjects();
}

void Zombie::CleanObjects() {
  delete bt_body_;
  bt_body_ = nullptr;
  delete bt_motion_;
  bt_motion_ = nullptr;
  delete bt_shape_;
  bt_shape_ = nullptr;
}
