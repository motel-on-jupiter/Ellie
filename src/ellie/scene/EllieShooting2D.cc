/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "ellie/scene/EllieShooting2D.h"
#include "util/macro_util.h"

EllieShooting2D::EllieShooting2D() {
}

EllieShooting2D::~EllieShooting2D() {
}

int EllieShooting2D::Initialize(const glm::vec2 &window_size) {
  UNUSED(window_size);
  return 0;
}

void EllieShooting2D::Finalize() {
}

void EllieShooting2D::Update(float elapsed_time, const glm::vec2 &window_size) {
  UNUSED(elapsed_time);
  UNUSED(window_size);
}

void EllieShooting2D::Draw(const glm::vec2 &window_size) {
  UNUSED(window_size);
}

int EllieShooting2D::OnMouseButtonDown(unsigned char button,
                                       const glm::vec2 &cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);
  return 0;
}
