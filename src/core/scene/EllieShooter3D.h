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
#include "scene/BaseScene.h"
#include "scene/GraphDrivenScene.h"
#include "scene/SceneGraph.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"
#include "wrapping/bullet_wrap.h"

#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"

class ShooterPlayer : public CubicEntity, public CubicEntityPhysics {
 public:
  ShooterPlayer(const glm::vec3 &pos, const glm::quat &rot);
  virtual ~ShooterPlayer();

  virtual bool Initialize();
  virtual void Finalize();

 private:
  btSphereShape *colli_shape_;
};

class ShooterBullet : public CubicEntity, public EntitySphereDraw {
 public:
  static const float kSpeed;

  ShooterBullet(const glm::vec3 &pos, const glm::quat &rot);
  virtual ~ShooterBullet();

  void Update(float elapsed_time) {
    prev_pos_ = pos();
    Move(rot() * glm::vec3(0.0f, 0.0f, kSpeed) * elapsed_time);
  }

  const glm::vec3 &prev_pos() const {
    return prev_pos_;
  }
  const glm::vec3 &velocity() const {
    return velocity_;
  }

 private:
  glm::vec3 prev_pos_;
  glm::vec3 velocity_;
};

class EllieShooter3DIngame : public BaseScene {
 public:
  static const float kBulletVanishDistance;
  static const float kZombieSpawnInterval;
  static const unsigned int kMaxZombies;

  EllieShooter3DIngame(Camera &camera);
  virtual ~EllieShooter3DIngame();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(const SDL_KeyboardEvent &key);
  virtual void OnKeyUp(const SDL_KeyboardEvent &key);
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnStep(float elapsed_time);

 private:
  void CleanObjects();

  btDefaultCollisionConfiguration* bt_colli_config_;
  btDispatcher* bt_dispatcher_;
  btBroadphaseInterface* bt_overlap_cache_;
  btSequentialImpulseConstraintSolver *bt_solver_;
  btDiscreteDynamicsWorld* bt_world_;
  Camera &camera_;
  FirstPersonCameraController camera_controller_;
  ShooterPlayer *player_;
  std::vector<Zombie *> zombies_;
  std::vector<ShooterBullet *> bullets_;
  float spawn_timer_;
};

class EllieShooter3D : public GraphDrivenScene {
 public:
  EllieShooter3D();
  virtual ~EllieShooter3D();

  virtual void Draw(const glm::vec2 &window_size);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();

 private:
  Camera camera_;
  GridStage3D stage_;
  std::vector<BaseScene *> scene_pool_;
  SceneGraph scene_graph_;
};

#endif /* ELLIE_SHOOTER_3D_H_ */
