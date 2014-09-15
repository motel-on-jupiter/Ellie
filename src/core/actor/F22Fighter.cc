/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "F22Fighter.h"
#include "entity/PlanarEntity.h"
#include "entity/PlanarEntityDraw.h"
#include "util/catalogue/color_sample.h"

FighterBullet::FighterBullet()
: PlanarEntity(glm::vec2(0.0f), 0.0f, glm::vec2(2.0f)),
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
: PlanarEntity(glm::vec2(0.0f), 0.0f, glm::vec2(18.92f, 13.56f)),
  EntityTriangleDraw(*this, true, X11Color::kGray) {
}

F22Fighter::~F22Fighter() {
}

void F22Fighter::Initialize(const glm::vec2 &pos, float rot) {
  set_pos(pos);
  set_rot(rot);
}

void F22Fighter::MoveForward() {
  Move(glm::vec2(0.0f, -1.0f));
}

void F22Fighter::MoveBack() {
  Move(glm::vec2(0.0f, 1.0f));
}

void F22Fighter::MoveLeft() {
  Move(glm::vec2(-1.0f, 0.0f));
}

void F22Fighter::MoveRight() {
  Move( glm::vec2(1.0f, 0.0f));
}

glm::vec2 F22Fighter::GetShotPos(bool left) const {
  glm::vec2 offset = glm::vec2(2.0f, 0.0f);
  if (left) {
    offset *= -1.0f;
  }
  return pos() + offset;
}
