/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntity.h"
#include "auxiliary/glm_aux.h"

EntitySphereDraw::EntitySphereDraw(CubicEntity &entity, bool fill, int slices,
                                   int stacks,
                                   const GLMaterialColor &material_color)
    : CubicEntityDraw(entity, material_color),
      fill_(fill),
      slices_(slices),
      stacks_(stacks) {
}

void EntitySphereDraw::Draw() const {
  glColor3fv(glm::value_ptr(material_color().ambient));
  glMaterial(GL_FRONT, material_color());
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(entity().BuildTransformMatrix()));
  if (fill_) {
    glutSolidSphere(0.5, slices_, stacks_);
  } else {
    glutWireSphere(0.5, slices_, stacks_);
  }
  glPopMatrix();
}

EntityCubeDraw::EntityCubeDraw(CubicEntity &entity, bool fill,
                               const GLMaterialColor &material_color)
    : CubicEntityDraw(entity, material_color),
      fill_(fill) {
}

void EntityCubeDraw::Draw() const {
  glColor3fv(glm::value_ptr(material_color().ambient));
  glMaterial(GL_FRONT, material_color());
  glPushMatrix();
  glMultMatrixf(
      glm::value_ptr(
          glm::translate(
              entity().pos() + glm_aux::y_dir() * entity().scale() * 0.5f)
              * glm::toMat4(entity().rot()) * glm::scale(entity().scale())));
  if (fill_) {
    glutSolidCube(1.0);
  } else {
    glutWireCube(1.0);
  }
  glPopMatrix();
}
