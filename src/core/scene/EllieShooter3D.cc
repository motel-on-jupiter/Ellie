/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "EllieShooter3D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/logging/Logger.h"
#include "util/wrapper/glgraphics_wrap.h"

ShooterBullet::ShooterBullet(const glm::vec3 &pos, const glm::quat &rot,
                             float speed)
    : CubicEntity(pos, rot, glm::vec3(0.1f, 0.1f, 2.0f)),
      EntitySphereDraw(*this, true, 10, 10,
                       GLMaterialColor(X11Color::to_fvec(X11Color::kDeepPink))),
      CubicEntityPhysics(*this, glm::vec3(0.0f, 0.0f, speed)) {
}

ShooterBullet::~ShooterBullet() {
}

EllieShooter3D::EllieShooter3D()
    : EllieBaseGameScene("3D Shooter"),
      camera_(glm::vec3(0.0f, 1.5f, -5.0f), glm::vec3(0.0f),
              glm::vec3(0.0f, 1.0f, 0.0f)),
      camera_controller_(camera_, 5.0f, 0.015f),
      stage_(glm::vec3(1000.0f, 10.0f, 1000.0f)),
      zombie_(),
      bullets_() {
}

EllieShooter3D::~EllieShooter3D() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    free(*it);
  }
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
  zombie_.Draw();

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
        glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), camera_.BuildForwardDir()),
        150.0f);
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
  return 0;
}

void EllieShooter3D::OnFinal() {
  for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
    free(*it);
  }
  bullets_.clear();
}

void EllieShooter3D::OnUpdate(float elapsed_time) {
  camera_controller_.Update(elapsed_time);
  for (auto it = bullets_.begin(); it != bullets_.end();) {
    (*it)->Update(elapsed_time);
    if (glm::distance2((*it)->pos(), camera_.pos()) > 1000.0f) {
      delete *it;
      it = bullets_.erase(it);
    } else {
      ++it;
    }
  }
}

