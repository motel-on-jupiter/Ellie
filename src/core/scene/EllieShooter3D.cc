/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "EllieShooter3D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/auxiliary/glm_aux.h"
#include "util/auxiliary/math_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/logging/Logger.h"
#include "util/wrapper/glgraphics_wrap.h"

const float ShooterBullet::kSpeed = 150.0f;

ShooterBullet::ShooterBullet(const glm::vec3 &pos, const glm::quat &rot)
    : CubicEntity(pos, rot, glm::vec3(0.1f, 0.1f, 2.0f)),
      EntitySphereDraw(*this, true, 10, 10,
                       GLMaterialColor(X11Color::to_fvec(X11Color::kDeepPink))) {
}

ShooterBullet::~ShooterBullet() {
}

const float EllieShooter3D::kBulletVanishDistance = 100.0f;

EllieShooter3D::EllieShooter3D()
    : EllieBaseGameScene("3D Shooter"),
      bt_colli_config_(nullptr),
      bt_dispatcher_(nullptr),
      bt_overlap_cache_(nullptr),
      bt_solver_(nullptr),
      bt_world_(nullptr),
      camera_(glm::vec3(0.0f, 1.5f, -5.0f), glm::vec3(0.0f),
              glm::vec3(0.0f, 1.0f, 0.0f)),
      camera_controller_(camera_, 5.0f, 0.015f),
      stage_(glm::vec3(1000.0f, 10.0f, 1000.0f)),
      zombie_(),
      bullets_() {
}

EllieShooter3D::~EllieShooter3D() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    delete *it;
  }
  if ((bt_world_ != nullptr) && (zombie_.bt_body() != nullptr)) {
    bt_world_->removeRigidBody(zombie_.bt_body());
  }
  CleanObjects();
}

void EllieShooter3D::Draw(const glm::vec2 &window_size) {
  glClearAll();

  glPushMatrix();
  glViewport(0, 0, static_cast<GLsizei>(window_size.x),
             static_cast<GLsizei>(window_size.y));
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(
          glm::perspective(glm::radians(45.0f), window_size.x / window_size.y,
                           0.1f, 1000.0f)));

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(camera_.BuildLookAt()));

  static const GLfloat kLightPosition[] = { 0.0f, 10.0f, 10.0f };
  static const GLfloat kLightAmbientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static const GLfloat kLightDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static const GLfloat kLightSpecularColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, kLightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, kLightAmbientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, kLightDiffuseColor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, kLightSpecularColor);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  stage_.Draw();
  if (!zombie_.IsDead()) {
    zombie_.Draw();
  }

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    (*it)->Draw();
  }

  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
}

void EllieShooter3D::OnKeyDown(const SDL_KeyboardEvent &keyboard) {
  camera_controller_.OnKeyDown(keyboard);
}

void EllieShooter3D::OnKeyUp(const SDL_KeyboardEvent &keyboard) {
  camera_controller_.OnKeyUp(keyboard);
}

void EllieShooter3D::OnMouseButtonDown(const SDL_MouseButtonEvent &button) {
  if (button.button == SDL_BUTTON_LEFT) {
    ShooterBullet *bullet = new ShooterBullet(
        camera_.pos(),
        glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), camera_.BuildForwardDir()));
    if (bullet == nullptr) {
      LOGGER.Error("Failed to allocate for bullet object");
    }
    bullets_.push_back(bullet);
  }
}

void EllieShooter3D::OnMouseMotion(const SDL_MouseMotionEvent &motion) {
  camera_controller_.OnMouseMotion(motion);
}

int EllieShooter3D::OnInitial() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);

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

  if (!zombie_.Initialize()) {
    LOGGER.Error(
        "Failed to allocate for Bullet collision configuration object");
    CleanObjects();
    return -1;
  }
  bt_world_->addRigidBody(zombie_.bt_body());

  return 0;
}

void EllieShooter3D::OnFinal() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    delete *it;
  }
  bullets_.clear();
  bt_world_->removeRigidBody(zombie_.bt_body());
  zombie_.Finalize();
  CleanObjects();
}

void EllieShooter3D::OnUpdate(float elapsed_time) {
  camera_controller_.Update(elapsed_time);
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
    bt_world_->rayTest(glm_aux::castToBt(bullet->prev_pos()),
                       glm_aux::castToBt(bullet->pos()), test_result);
    if (test_result.hasHit()) {
      zombie_.TakeDamage();
      delete bullet;
      it = bullets_.erase(it);
      continue;
    }
    ++it;
  }
}

void EllieShooter3D::CleanObjects() {
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
