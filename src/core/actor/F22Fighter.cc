/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "F22Fighter.h"
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "util/catalogue/color_sample.h"

F22Fighter::F22Fighter()
: BaseEntity(glm::vec2(0.0f), 0.0f, glm::vec2(18.92f, 13.56f)),
  EntityTriangleDraw(*this, true, X11Color::kGray) {
}

F22Fighter::~F22Fighter() {
}

void F22Fighter::Initialize(const glm::vec2 &pos, float rot) {
  set_pos(pos);
  set_rot(rot);
}
