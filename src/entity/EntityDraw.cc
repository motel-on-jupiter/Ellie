/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "entity/EntityDraw.h"
#include <glm/gtx/rotate_vector.hpp>
#include "entity/BaseEntity.h"

EntityPointDraw::EntityPointDraw(BaseEntity &entity, const GLubyte *color) :
  EntityDraw(entity, color) {
}

void EntityPointDraw::Draw() const {
  if (color() != nullptr) {
    glColor3ubv(color());
  }
  glPointSize(entity().scale().x);
  glBegin(GL_POINTS);
  glVertex2fv(glm::value_ptr(entity().pos()));
  glEnd();
}

EntityCircleDraw::EntityCircleDraw(BaseEntity &entity, unsigned int splits, bool fill, const GLubyte *color) :
  EntityDraw(entity, color), splits_(splits), fill_(fill) {
}

void EntityCircleDraw::Draw() const {
  if (color() != nullptr) {
    glColor3ubv(color());
  }
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(entity().pos(), 0.0f))));
  glBegin(fill_ ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
  for (unsigned int i=0; i<splits_; ++i ) {
    float rot =
        entity().rot() +
        2.0f * glm::pi<float>() * static_cast<float>(i) / static_cast<float>(splits_);
    glVertex2fv(
        glm::value_ptr(
            entity().scale() * glm::vec2(0.5f * cos(rot), 0.5f * sin(rot))));
  }
  glEnd();
  glPopMatrix();
}

EntityTriangleDraw::EntityTriangleDraw(BaseEntity &entity, bool fill, const GLubyte *color) :
  EntityDraw(entity, color), fill_(fill) {
}

void EntityTriangleDraw::Draw() const {
  if (color() != nullptr) {
    glColor3ubv(color());
  }
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(entity().pos(), 0.0f))));
  glBegin(fill_ ? GL_TRIANGLES : GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(entity().scale() * glm::vec2(0.0f, -0.5f), entity().rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(glm::vec2(entity().scale() * glm::vec2(-0.5f, 0.5f)), entity().rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(glm::vec2(entity().scale() * glm::vec2(0.5f, 0.5f)), entity().rot())));
  glEnd();
  glPopMatrix();
}

EntityRectangleDraw::EntityRectangleDraw(BaseEntity &entity, bool fill, const GLubyte *color) :
  EntityDraw(entity, color), fill_(fill) {
}

void EntityRectangleDraw::Draw() const {
  if (color() != nullptr) {
    glColor3ubv(color());
  }
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(glm::translate(glm::vec3(entity().pos(), 0.0f))));
  glBegin(fill_ ? GL_QUADS : GL_LINE_LOOP);
  glVertex2fv(glm::value_ptr(glm::rotate(entity().scale() * -0.5f, entity().rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(entity().scale() * glm::vec2(-0.5f, 0.5f), entity().rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(entity().scale() * 0.5f, entity().rot())));
  glVertex2fv(glm::value_ptr(glm::rotate(entity().scale() * glm::vec2(0.5f, -0.5f), entity().rot())));
  glEnd();
  glPopMatrix();
}
