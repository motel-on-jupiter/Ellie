/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTER_3D_H_
#define ELLIE_SHOOTER_3D_H_

#include <vector>
#include "camera/FirstPersonCameraController.h"
#include "core/actor/Zombie.h"
#include "core/stage/GridStage3D.h"
#include "core/EllieGame.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"
#include "util/wrapper/bullet_wrap.h"

class ShooterBullet : public CubicEntity, public CubicEntityPhysics,
    public EntitySphereDraw {
 public:
  ShooterBullet(const glm::vec3 &pos, const glm::quat &rot, float speed);
  virtual ~ShooterBullet();
};

class EllieShooter3D : public EllieBaseGameScene {
 public:
  EllieShooter3D();
  virtual ~EllieShooter3D();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(const SDL_KeyboardEvent &key);
  virtual void OnKeyUp(const SDL_KeyboardEvent &key);
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 protected:
  static const float EllieShooter3D::kBulletVanishDistance;

  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnUpdate(float elapsed_time);

 private:
  void CleanObjects();

  btDefaultCollisionConfiguration* bt_colli_config_;
  btDispatcher* bt_dispatcher_;
  btBroadphaseInterface* bt_overlap_cache_;
  btSequentialImpulseConstraintSolver *bt_solver_;
  btDiscreteDynamicsWorld* bt_world_;
  Camera camera_;
  FirstPersonCameraController camera_controller_;
  GridStage3D stage_;
  Zombie zombie_;
  std::vector<ShooterBullet *> bullets_;
};

#endif /* ELLIE_SHOOTER_3D_H_ */
