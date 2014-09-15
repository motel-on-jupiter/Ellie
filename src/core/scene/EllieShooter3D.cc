/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "EllieShooter3D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/wrapper/glgraphics_wrap.h"

EllieShooter3D::EllieShooter3D()
    : EllieBaseGameScene("3D Shooter"),
      stage_(glm::vec3(1000.0f, 10.0f, 1000.0f), X11Color::kDarkGreen) {
}

EllieShooter3D::~EllieShooter3D() {
}

int EllieShooter3D::Initialize() {
  glSetClearingColor(0.0f, 0.0f, 0.0f, 0.0f);
  return 0;
}

void EllieShooter3D::Finalize() {
}

void EllieShooter3D::Update(float elapsed_time) {
  UNUSED(elapsed_time);
}

void EllieShooter3D::Draw(const glm::vec2 &window_size) {
  glClearAll();

  glPushMatrix();
  glViewport(0, 0, static_cast<GLsizei>(window_size.x),
             static_cast<GLsizei>(window_size.y));
  glEnable (GL_DEPTH_TEST);

  glMatrixMode (GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(
          glm::perspective(glm::radians(45.0f), window_size.x / window_size.y,
                           1.0f, 1000.0f)));

  glMatrixMode (GL_MODELVIEW);
  glLoadMatrixf(
      glm::value_ptr(
          glm::lookAt(glm::vec3(0.0f, 1.5f, -30.0f), glm::vec3(0.0f),
                      glm::vec3(0.0f, 1.0f, 0.0f))));

  static const GLfloat kLightPosition[] = { 0.0f, 10.0f, -10.0f, 1.0f };
  static const GLfloat kLightAmbientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static const GLfloat kLightDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  static const GLfloat kLightSpecularColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, kLightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, kLightAmbientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, kLightDiffuseColor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, kLightSpecularColor);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);

  stage_.Draw();

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
}

void EllieShooter3D::OnKeyDown(SDL_Keycode key) {
  UNUSED(key);
}

void EllieShooter3D::OnKeyUp(SDL_Keycode key) {
  UNUSED(key);
}
