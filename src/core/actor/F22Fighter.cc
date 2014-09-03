/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "F22Fighter.h"
#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"
#include "util/catalogue/color_sample.h"

FighterBullet::FighterBullet()
: BaseEntity(glm::vec2(0.0f), 0.0f, glm::vec2(2.0f)),
  EntityPointDraw(*this, X11Color::kOrange),
  vel_(0.0f),
  life_time_(-1.0f) {
}

FighterBullet::~FighterBullet() {
}

void FighterBullet::Initialize(const glm::vec2 &pos, const glm::vec2 &vel) {
  set_pos(pos);
  vel_ = vel;
  life_time_ = 5.0f;
}

void FighterBullet::Update(float elapsed_time) {
  if (life_time_ < 0.0f) {
    return;
  }
  Move(vel_ * elapsed_time);
  life_time_ -= elapsed_time;
}

void FighterBullet::Draw() {
  if (life_time_ < 0.0f) {
    return;
  }
  EntityPointDraw::Draw();
}

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

glm::vec2 F22Fighter::GetShotPos(bool left) const {
  glm::vec2 offset = glm::vec2(2.0f, 0.0f);
  if (left) {
    offset *= -1.0f;
  }
  return pos() + offset;
}
