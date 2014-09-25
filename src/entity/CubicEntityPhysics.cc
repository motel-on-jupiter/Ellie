/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/CubicEntityPhysics.h"
#include "util/auxiliary/glm_aux.h"
#include "util/logging/Logger.h"
#include "util/wrapper/bullet_wrap.h"

bool CubicEntityPhysics::Initialize() {
  bt_shape_ = new btBoxShape(glm_aux::toBtVec3(entity().scale() * 0.5f));
  if (bt_shape_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet collsion shape object");
    return false;
  }
  bt_motion_ = new CubicEntityMotionState(entity());
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
  bt_body_ = nullptr;
  bt_motion_ = nullptr;
  bt_shape_ = nullptr;
}

void CubicEntityPhysics::CleanObjects() {
  delete bt_body_;
  delete bt_motion_;
  delete bt_shape_;
}
