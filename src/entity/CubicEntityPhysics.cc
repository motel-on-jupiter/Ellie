/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/CubicEntityPhysics.h"
#include "util/auxiliary/glm_aux.h"
#include "util/logging/Logger.h"
#include "util/wrapper/bullet_wrap.h"

bool CubicEntityPhysics::Initialize() {
  bt_shape_ = new btBoxShape(glm_aux::castToBt(entity().scale() * 0.5f));
  if (bt_shape_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet collsion shape object");
    return false;
  }
  glm::vec3 motion_pos = entity().pos()
      + glm::vec3(0.0f, entity().scale().y * 0.5f, 0.0f);
  bt_motion_ = new btDefaultMotionState(
      btTransform(glm_aux::castToBt(entity().rot()), glm_aux::castToBt(motion_pos)));
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

void CubicEntityPhysics::Finalize() {
  CleanObjects();
}

void CubicEntityPhysics::CleanObjects() {
  delete bt_body_;
  bt_body_ = nullptr;
  delete bt_motion_;
  bt_motion_ = nullptr;
  delete bt_shape_;
  bt_shape_ = nullptr;
}
