/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/CubicEntityPhysics.h"
#include "util/auxiliary/glm_aux.h"
#include "util/logging/Logger.h"
#include "util/wrapper/bullet_wrap.h"

bool CubicEntityPhysics::Initialize(btCollisionShape &shape) {
  bt_motion_ = new CubicEntityMotionState(entity());
  if (bt_motion_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet motion state object");
    CleanObjects();
    return false;
  }
  bt_body_ = new btRigidBody(
      btRigidBody::btRigidBodyConstructionInfo(1, bt_motion_, &shape));
  if (bt_body_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet rigid body object");
    CleanObjects();
    return false;
  }
  return true;
}

void CubicEntityPhysics::Finalize() {
  CleanObjects();
  bt_body_ = nullptr;
  bt_motion_ = nullptr;
}

void CubicEntityPhysics::CleanObjects() {
  delete bt_body_;
  delete bt_motion_;
}
