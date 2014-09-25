/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CUBIC_ENTITY_PHYSICS_H_
#define CUBIC_ENTITY_PHYSICS_H_

#include <boost/noncopyable.hpp>
#include "entity/CubicEntity.h"
#include "util/auxiliary/glm_aux.h"
#include "util/wrapper/bullet_wrap.h"

class CubicEntityMotionState : public btMotionState, boost::noncopyable {
 public:
  CubicEntityMotionState(CubicEntity &entity)
      : entity_(entity) {
  }
  virtual ~CubicEntityMotionState() {
  }

  virtual void getWorldTransform(btTransform& worldTrans) const {
    worldTrans.setOrigin(
        glm_aux::toBtVec3(
            entity_.pos() + glm_aux::y_dir() * entity_.scale() * 0.5f));
    worldTrans.setRotation(glm_aux::toBtQuat(entity_.rot()));
  }
  virtual void setWorldTransform(const btTransform& worldTrans) {
    entity_.MoveTo(
        glm_aux::fromBtVec3(worldTrans.getOrigin())
            - glm_aux::y_dir() * entity_.scale() * 0.5f);
    entity_.RotateTo(glm_aux::fromBtQuat(worldTrans.getRotation()));
  }

 private:
  CubicEntity &entity_;
};

class CubicEntityPhysics : public CubicEntityMixIn {
 public:
  CubicEntityPhysics(CubicEntity &entity)
      : CubicEntityMixIn(entity),
        bt_shape_(nullptr),
        bt_motion_(nullptr),
        bt_body_(nullptr) {
  }
  virtual ~CubicEntityPhysics() {
    CleanObjects();
  }

  virtual bool Initialize();
  virtual void Finalize();

  virtual void SetVelocity(const glm::vec3 &velocity) {
    bt_body()->setLinearVelocity(glm_aux::toBtVec3(velocity));
  }
  virtual void SetAngularVelocity(const glm::vec3 &velocity) {
    bt_body()->setAngularVelocity(glm_aux::toBtVec3(velocity));
  }
  virtual void SetAngularVelocity(const glm::quat &rotation) {
    bt_body()->setAngularVelocity(btVector3(glm::pitch(rotation), glm::yaw(rotation), glm::roll(rotation)));
  }

  btRigidBody *bt_body() {
    return bt_body_;
  }

 private:
  void CubicEntityPhysics::CleanObjects();

  btCollisionShape *bt_shape_;
  btMotionState *bt_motion_;
  btRigidBody* bt_body_;
};

#endif /* CUBIC_ENTITY_PHYSICS_H_ */
