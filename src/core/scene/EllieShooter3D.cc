/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "EllieShooter3D.h"
#include "core/actor/Zombie.h"
#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"
#include "scene/BaseScene.h"
#include "scene/GraphDrivenScene.h"
#include "scene/SceneGraph.h"
#include "scene/TitleScene.h"
#include "util/auxiliary/assert_aux.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/auxiliary/glm_aux.h"
#include "util/auxiliary/math_aux.h"
#include "util/sampler/color_sampler.h"
#include "util/logging/Logger.h"
#include "util/wrapper/glgraphics_wrap.h"

ShooterPlayer::ShooterPlayer(const glm::vec3 &pos, const glm::quat &rot)
    : CubicEntity(pos, rot, glm::vec3(1.0f, 1.75f, 0.3f)),
      CubicEntityPhysics(*static_cast<CubicEntity *>(this)),
      colli_shape_(nullptr) {
}

ShooterPlayer::~ShooterPlayer() {
  delete colli_shape_;
}

bool ShooterPlayer::Initialize() {
  colli_shape_ = new btSphereShape(0.5f);
  if (colli_shape_ == nullptr) {
    LOGGER.Error("Failed to allocate collision shape object");
    return false;
  }
  if (!CubicEntityPhysics::Initialize(*colli_shape_)) {
    delete colli_shape_;
    colli_shape_ = nullptr;
    return false;
  }
  return true;
}

void ShooterPlayer::Finalize() {
  CubicEntityPhysics::Finalize();
  delete colli_shape_;
  colli_shape_ = nullptr;
}

const float ShooterBullet::kSpeed = 150.0f;

ShooterBullet::ShooterBullet(const glm::vec3 &pos, const glm::quat &rot)
    : CubicEntity(pos, rot, glm::vec3(0.1f, 0.1f, 2.0f)),
      EntitySphereDraw(*this, true, 10, 10,
                       GLMaterialColor(X11Color::to_fvec(X11Color::kDeepPink))) {
}

ShooterBullet::~ShooterBullet() {
}

const float EllieShooter3DIngame::kBulletVanishDistance = 100.0f;
const float EllieShooter3DIngame::kZombieSpawnInterval = 5.0f;
const unsigned int EllieShooter3DIngame::kMaxZombies = 5;

EllieShooter3DIngame::EllieShooter3DIngame(Camera &camera)
    : BaseScene("3D Shooter"),
      bt_colli_config_(nullptr),
      bt_dispatcher_(nullptr),
      bt_overlap_cache_(nullptr),
      bt_solver_(nullptr),
      bt_world_(nullptr),
      camera_(camera),
      camera_controller_(camera_, 5.0f, 0.015f),
      player_(nullptr),
      zombies_(),
      bullets_(),
      spawn_timer_(0.0f) {
}

EllieShooter3DIngame::~EllieShooter3DIngame() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    delete *it;
  }
  if (bt_world_ != nullptr) {
    for (auto it = zombies_.begin(); it != zombies_.end(); ++it) {
      bt_world_->removeRigidBody((*it)->bt_body());
      delete *it;
    }
  }
  CleanObjects();
}

void EllieShooter3DIngame::Draw(const glm::vec2 &window_size) {
  UNUSED(window_size);

  glPushMatrix();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  for (auto it = zombies_.begin(); it != zombies_.end(); ++it) {
    (*it)->Draw();
  }
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    (*it)->Draw();
  }

  glPopMatrix();
}

void EllieShooter3DIngame::OnKeyDown(const SDL_KeyboardEvent &keyboard) {
  camera_controller_.OnKeyDown(keyboard);
}

void EllieShooter3DIngame::OnKeyUp(const SDL_KeyboardEvent &keyboard) {
  camera_controller_.OnKeyUp(keyboard);
}

void EllieShooter3DIngame::OnMouseButtonDown(
    const SDL_MouseButtonEvent &button) {
  if (button.button == SDL_BUTTON_LEFT) {
    ShooterBullet *bullet = new ShooterBullet(
        camera_.pos(),
        glm::rotation(glm_aux::z_dir(), camera_.BuildForwardDir()));
    if (bullet == nullptr) {
      LOGGER.Error("Failed to allocate for bullet object");
    }
    bullets_.push_back(bullet);
  }
}

void EllieShooter3DIngame::OnMouseMotion(const SDL_MouseMotionEvent &motion) {
  camera_controller_.OnMouseMotion(motion);
}

int EllieShooter3DIngame::OnInitial() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);

  static const GLfloat kLightPosition[] = { 0.0f, 10.0f, 10.0f };
  static const GLfloat kLightAmbientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static const GLfloat kLightDiffuseColor[] = { 0.1f, 0.1f, 0.1f, 0.1f };
  static const GLfloat kLightSpecularColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, kLightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, kLightAmbientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, kLightDiffuseColor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, kLightSpecularColor);

  bt_colli_config_ = new btDefaultCollisionConfiguration();
  if (bt_colli_config_ == nullptr) {
    LOGGER.Error(
        "Failed to allocate for Bullet collision configuration object");
    CleanObjects();
    return -1;
  }
  bt_dispatcher_ = new btCollisionDispatcher(bt_colli_config_);
  if (bt_dispatcher_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet dispatcher object");
    CleanObjects();
    return -1;
  }
  bt_overlap_cache_ = new btDbvtBroadphase();
  if (bt_overlap_cache_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet overlapping pair cache object");
    CleanObjects();
    return -1;
  }
  bt_solver_ = new btSequentialImpulseConstraintSolver();
  if (bt_solver_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet solver object");
    CleanObjects();
    return -1;
  }
  bt_world_ = new btDiscreteDynamicsWorld(bt_dispatcher_, bt_overlap_cache_,
                                          bt_solver_, bt_colli_config_);
  if (bt_world_ == nullptr) {
    LOGGER.Error("Failed to allocate for Bullet world object");
    CleanObjects();
    return -1;
  }
  bt_world_->setGravity(glm_aux::toBtVec3(glm::vec3()));

  player_ = new ShooterPlayer(camera_.pos(), camera_.BuildRotation());
  if (player_ == nullptr) {
    LOGGER.Error("Failed to allocate for player object");
    CleanObjects();
    return -1;
  }
  if (!player_->Initialize()) {
    LOGGER.Error("Failed to initialize player object");
    CleanObjects();
    return -1;
  }
  bt_world_->addRigidBody(player_->bt_body());
  player_->bt_body()->setUserPointer(player_);

  spawn_timer_ = 0.0f;

  return 0;
}

void EllieShooter3DIngame::OnFinal() {
  CleanObjects();
}

void EllieShooter3DIngame::OnStep(float elapsed_time) {
  /* For camera and player */
  glm::vec3 before_camera_pos = camera_.pos();
  //glm::quat before_camera_rot = camera_.BuildRotation();
  camera_controller_.Update(elapsed_time);
  glm::vec3 player_velocity = (camera_.pos() - before_camera_pos) /=
      elapsed_time;
  player_velocity.y = 0.0f;
  player_->SetVelocity(player_velocity);

  /* For entity objects */
  for (auto it = zombies_.begin(); it != zombies_.end(); ++it) {
    (*it)->Update(camera_.pos(), 1.0f / elapsed_time);
  }
  if (zombies_.size() < kMaxZombies) {
    spawn_timer_ += elapsed_time;
    if (spawn_timer_ > kZombieSpawnInterval) {
      float angle = glm::linearRand(0.0f, glm::radians(360.0f));
      Zombie *zombie = new Zombie(
          camera_.pos() * glm::vec3(1.0f, 0.0f, 1.0f)
              + glm::rotateY(glm_aux::z_dir() * -1.0f, angle) * 10.0f,
          glm_aux::angleAxisY(angle));
      if (zombie == nullptr) {
        LOGGER.Error("Failed to allocate for zombie object");
      } else {
        if (zombie->Initialize()) {
          bt_world_->addRigidBody(zombie->bt_body());
          zombie->bt_body()->setUserPointer(zombie);
          zombies_.push_back(zombie);
        } else {
          LOGGER.Error("Failed to initialize zombie");
          delete zombie;
        }
      }
      spawn_timer_ -= kZombieSpawnInterval;
    }
  }

  /* For physics with Bullet */
  bt_world_->stepSimulation(elapsed_time, 60);

  /* For physics, collision detection and collided reaction */
  for (auto it = bullets_.begin(); it != bullets_.end();) {
    ShooterBullet *bullet = *it;
    bullet->Update(elapsed_time);
    if (glm::distance2(bullet->pos(), camera_.pos())
        > math_aux::square(kBulletVanishDistance)) {
      delete bullet;
      it = bullets_.erase(it);
      continue;
    }

    btCollisionWorld::ClosestRayResultCallback test_result =
        btCollisionWorld::ClosestRayResultCallback(btVector3(), btVector3());
    bt_world_->rayTest(glm_aux::toBtVec3(bullet->prev_pos()),
                       glm_aux::toBtVec3(bullet->pos()), test_result);
    if (test_result.hasHit()) {
      Zombie *zombie = static_cast<Zombie *>(test_result.m_collisionObject
          ->getUserPointer());
      ASSERT(zombie != nullptr);
      if (!(zombie->IsDead())) {
        zombie->TakeDamage();
        delete bullet;
        it = bullets_.erase(it);
        continue;
      }
    }
    ++it;
  }
  camera_.set_pos(player_->pos());
  for (auto it = zombies_.begin(); it != zombies_.end();) {
    if ((*it)->IsDead()) {
      bt_world_->removeRigidBody((*it)->bt_body());
      (*it)->Finalize();
      delete *it;
      it = zombies_.erase(it);
    } else {
      ++it;
    }
  }
}

void EllieShooter3DIngame::CleanObjects() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    delete *it;
  }
  bullets_.clear();
  for (auto it = zombies_.begin(); it != zombies_.end(); ++it) {
    if (bt_world_ != nullptr) {
      bt_world_->removeRigidBody((*it)->bt_body());
    }
    (*it)->Finalize();
    delete *it;
  }
  zombies_.clear();
  if (player_ != nullptr) {
    if (bt_world_ != nullptr) {
      bt_world_->removeRigidBody(player_->bt_body());
    }
    player_->Finalize();
    delete player_;
    player_ = nullptr;
  }
  delete bt_world_;
  bt_world_ = nullptr;
  delete bt_solver_;
  bt_solver_ = nullptr;
  delete bt_overlap_cache_;
  bt_overlap_cache_ = nullptr;
  delete bt_dispatcher_;
  bt_dispatcher_ = nullptr;
  delete bt_colli_config_;
  bt_colli_config_ = nullptr;
}

EllieShooter3D::EllieShooter3D()
    : GraphDrivenScene("3D Shooter", scene_graph_),
      camera_(glm::vec3(0.0f, 1.5f, -5.0f), glm::vec3(0.0f),
              glm::vec3(0.0f, 1.0f, 0.0f)),
      stage_(glm::vec3(1000.0f, 10.0f, 1000.0f)),
      scene_pool_(),
      scene_graph_() {
}

EllieShooter3D::~EllieShooter3D() {
}

void EllieShooter3D::Draw(const glm::vec2 &window_size) {
  glClearAll();

  glPushMatrix();
  glViewport(0, 0, static_cast<GLsizei>(window_size.x),
             static_cast<GLsizei>(window_size.y));

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(
          glm::perspective(glm::radians(45.0f), window_size.x / window_size.y,
                           0.1f, 1000.0f)));

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(camera_.BuildViewMatrix()));

  glEnable(GL_DEPTH_TEST);
  stage_.Draw();
  GraphDrivenScene::Draw(window_size);
  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
}

int EllieShooter3D::OnInitial() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);

  camera_.Reset();

  BaseScene *sub_scene = new TitleScene("Title");
  if (sub_scene == nullptr) {
    LOGGER.Error("Failed to allocate for sub scene object");
    return -1;
  }
  scene_pool_.push_back(sub_scene);

  sub_scene = new EllieShooter3DIngame(camera_);
  if (sub_scene == nullptr) {
    LOGGER.Error("Failed to allocate for sub scene object");
    return -1;
  }
  scene_pool_.push_back(sub_scene);

  SceneFlow flow = SceneFlow(nullptr, scene_pool_[0]);
  SceneEdge edge = SceneEdge(flow, 0);
  scene_graph_.push_back(edge);
  flow = SceneFlow(scene_pool_[0], scene_pool_[1]);
  edge = SceneEdge(flow, 0);
  scene_graph_.push_back(edge);

  int ret = GraphDrivenScene::OnInitial();
  if (ret < 0) {
    for (auto it = scene_pool_.begin(); it != scene_pool_.end(); ++it) {
      delete *it;
    }
    scene_pool_.clear();
    return ret;
  }
  return 0;
}

void EllieShooter3D::OnFinal() {
  GraphDrivenScene::OnFinal();
  for (auto it = scene_pool_.begin(); it != scene_pool_.end(); ++it) {
    delete *it;
  }
  scene_pool_.clear();
  scene_graph_.clear();
}
