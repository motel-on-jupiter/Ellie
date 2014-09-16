/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "graphics/GLMaterialColor.h"
#include "util/wrapper/glgraphics_wrap.h"

void glMaterial(GLenum face, const GLMaterialColor &material_color) {
  glMaterialfv(face, GL_AMBIENT, glm::value_ptr(material_color.ambient));
  glMaterialfv(face, GL_DIFFUSE, glm::value_ptr(material_color.diffuse));
  glMaterialfv(face, GL_SPECULAR, glm::value_ptr(material_color.specular));
  glMaterialfv(face, GL_SHININESS, &(material_color.shininess));
}
