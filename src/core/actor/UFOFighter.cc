/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "UFOFighter.h"
#include "entity/PlanarEntity.h"
#include "entity/PlanarEntityDraw.h"
#include "util/catalogue/color_sample.h"
#include "util/wrapper/coroutine_wrap.h"

UFOFighter::UFOFighter()
: PlanarEntity(glm::vec2(0.0f), 0.0f, glm::vec2(10.0f)),
  EntityCircleDraw(*this, 10, true, X11Color::kDeepPink),
  script_end_(true),
  ccr_(nullptr),
  timer_(0.0f),
  center_(glm::vec2(0.0f)) {
}

UFOFighter::~UFOFighter() {
  Finalize();
}

void UFOFighter::Initialize(const glm::vec2 &pos) {
  script_end_ = false;
  set_pos(pos);
}

void UFOFighter::Finalize() {
  ccrAbort(ccr_);
  script_end_ = true;
}

void UFOFighter::Update(float elapsed_time) {
  struct ccrContextTag **ccrParam = (struct ccrContextTag **) &ccr_;
  ccrBeginContext;
  ccrEndContext(ctx);

  ccrBegin_(ctx);
  while (script_end_) {
    ccrReturnV;
  }
  timer_ = 0.0f;
  for (timer_  += 1.0f; timer_ > 0.0f; timer_ -= elapsed_time) {
    Move(glm::vec2(0.0f, 200.0f) * elapsed_time);
    ccrReturnV;
  }
  center_ = pos();
  for (timer_  += 3.0f; timer_ > 0.0f; timer_ -= elapsed_time) {
    MoveTo(center_ + glm::vec2(50.0f, 0.0f) * sin(timer_ * glm::pi<float>()));
    ccrReturnV;
  }
  for (timer_ += 1.0f; timer_ > 0.0f; timer_ -= elapsed_time) {
    Move(glm::vec2(0.0f, -200.0f) * elapsed_time);
    ccrReturnV;
  }
  script_end_ = true;
  ccrFinishV;
}
