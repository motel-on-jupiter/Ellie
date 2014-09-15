/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "GridStage3D.h"
#include "util/wrapper/glgraphics_wrap.h"

GridStage3D::GridStage3D(const glm::vec3 &scale, const GLubyte (&color)[3])
    : scale_(scale) {
  memcpy(color_, color, sizeof(color_));
}

GridStage3D::~GridStage3D() {
}

void GridStage3D::Draw() {
  glColor3ubv(color_);
  glBegin (GL_LINES);
  for (float x = scale_.x * -0.5f + 1.0f; x < scale_.x * 0.5f; x += 1.0f) {
    glVertex3f(x, 0.0f, scale_.z * -0.5f);
    glVertex3f(x, 0.0f, scale_.z * 0.5f);
  }
  for (float z = scale_.z * -0.5f + 1.0f; z < scale_.z * 0.5f; z += 1.0f) {
    glVertex3f(scale_.x * -0.5f, 0.0f, z);
    glVertex3f(scale_.x * 0.5f, 0.0f, z);
  }
  glEnd();
}
