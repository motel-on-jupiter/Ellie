/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CUBIC_ENTITY_PHYSICS_H_
#define CUBIC_ENTITY_PHYSICS_H_

#include "entity/CubicEntity.h"

class btCollisionShape;
struct btDefaultMotionState;
class btRigidBody;

class CubicEntityPhysics : public CubicEntityMixIn {
 public:
  CubicEntityPhysics(CubicEntity &entity)
      : CubicEntityMixIn(entity),
        bt_shape_(nullptr),
        bt_motion_(nullptr),
        bt_body_(nullptr) {
  }
  virtual ~CubicEntityPhysics() {
    delete bt_body_;
    delete bt_motion_;
    delete bt_shape_;
  }

  virtual bool Initialize();
  virtual void Finalize();

  btDefaultMotionState *bt_motion() {
    return bt_motion_;
  }
  btRigidBody *bt_body() {
    return bt_body_;
  }

 private:
  void CubicEntityPhysics::CleanObjects();

  btCollisionShape *bt_shape_;
  btDefaultMotionState *bt_motion_;
  btRigidBody* bt_body_;
};

#endif /* CUBIC_ENTITY_PHYSICS_H_ */
