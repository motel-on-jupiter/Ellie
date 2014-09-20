/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/stage/GridStage3D.h"
#include <glm/gtx/quaternion.hpp>
#include "graphics/GLMaterialColor.h"
#include "util/catalogue/color_sample.h"
#include "util/wrapper/glgraphics_wrap.h"

GridStage3D::GridStage3D(const glm::vec3 &scale)
    : scale_(scale) {
}

GridStage3D::~GridStage3D() {
}

void GridStage3D::Draw() {
  glColor3ubv(X11Color::kDarkOrange);
  glPushMatrix();
  glMultMatrixf(
      glm::value_ptr(
          glm::translate(
              glm::vec3(0.0f)) * glm::toMat4(glm::quat()) * glm::scale(glm::vec3(1.0f))));
  glBegin(GL_LINES);
  for (float x = scale_.x * -0.5f + 1.0f; x < scale_.x * 0.5f; x += 1.0f) {
    glVertex3f(x, 0.0f, scale_.z * -0.5f);
    glVertex3f(x, 0.0f, scale_.z * 0.5f);
  }
  for (float z = scale_.z * -0.5f + 1.0f; z < scale_.z * 0.5f; z += 1.0f) {
    glVertex3f(scale_.x * -0.5f, 0.0f, z);
    glVertex3f(scale_.x * 0.5f, 0.0f, z);
  }
  glEnd();
  glPopMatrix();
}
