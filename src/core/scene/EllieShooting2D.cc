/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/scene/EllieShooting2D.h"
#include "util/catalogue/color_sample.h"
#include "util/wrapper/glgraphics_wrap.h"
#include "util/macro_util.h"

const size_t EllieShooting2DStage::kNumXMappingStars = 10;
const size_t EllieShooting2DStage::kNumYMappingStars = 10;
const int EllieShooting2DStage::kRatioMappingStars = 3;

EllieShooting2DStage::EllieShooting2DStage() {
  for (int i = 0; i < EllieShooting2DStage::kNumYMappingStars; ++i) {
    std::vector<bool> star_map_x;
    for (int j = 0; j < EllieShooting2DStage::kNumXMappingStars; ++j) {
      star_map_x.push_back(rand() % kRatioMappingStars == 0);
    }
    star_map_.push_back(star_map_x);
  }
}

EllieShooting2DStage::~EllieShooting2DStage() {
}

void EllieShooting2DStage::Draw(const glm::vec2 &window_size) {
  glm::vec2 mapping_interval = window_size
      / static_cast<float>(EllieShooting2DStage::kNumXMappingStars);
  glm::vec2 mapping_interval_x = mapping_interval * glm::vec2(1.0f, 0.0f);
  glm::vec2 mapping_interval_y = mapping_interval * glm::vec2(0.0f, 1.0f);

  glColor3ubv(X11Color::kYellow);
  glm::vec2 pos = mapping_interval * 0.5f;
  for (auto it = star_map_.begin(); it != star_map_.end(); ++it) {
    glm::vec2 star_pos = pos;
    for (auto star_it = (*it).begin(); star_it != (*it).end(); ++star_it) {
      if (*star_it) {
        if (rand() % 10 < 8) {
          glPointSize(2.0f);
        } else {
          glPointSize(1.0f);
        }
        glBegin(GL_POINTS);
        glVertex2fv(glm::value_ptr(star_pos));
        glEnd();
      }
      star_pos += mapping_interval_x;
    }
    pos += mapping_interval_y;
  }
}

const float EllieShooting2D::kShotInterval = 0.1f;

EllieShooting2D::EllieShooting2D()
    : stage_(), f22_(), shot_interval_(-1.0f) {
}

EllieShooting2D::~EllieShooting2D() {
}

int EllieShooting2D::Initialize(const glm::vec2 &window_size) {
  UNUSED(window_size);

  glSetClearingColor(0.0f, 0.0f, 0.0f, 0.0f);

  f22_.Initialize(glm::vec2(1000.0f, 1000.0f), 0.0f);
  return 0;
}

void EllieShooting2D::Finalize() {
}

void EllieShooting2D::Update(float elapsed_time, const glm::vec2 &window_size) {
  UNUSED(window_size);

  for (int i=0; i<ARRAYSIZE(bullets_); ++i) {
    bullets_[i].Update(elapsed_time);
  }
  if (shot_interval_ > 0.0f) {
    shot_interval_ -= elapsed_time;
  }
}

void EllieShooting2D::Draw(const glm::vec2 &window_size) {
  glClearAll();

  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(
          glm::ortho(0.0f, window_size.x, window_size.y, 0.0f, -1.0f, 1.0f)));
  glMatrixMode(GL_MODELVIEW);
  stage_.Draw(window_size);

  glMatrixMode(GL_PROJECTION);
  glm::vec2 focus_pos = glm::vec2(1000.0f, 900.0f);
  float zoom_ratio = 2.0f;
  glLoadMatrixf(
      glm::value_ptr(
          glm::ortho(focus_pos.x - window_size.x * 0.5f / zoom_ratio, focus_pos.x + window_size.x * 0.5f / zoom_ratio, focus_pos.y + window_size.y * 0.5f / zoom_ratio, focus_pos.y - window_size.y * 0.5f / zoom_ratio, -1.0f, 1.0f)));
  glMatrixMode(GL_MODELVIEW);
  for (int i=0; i<ARRAYSIZE(bullets_); ++i) {
    bullets_[i].Draw();
  }
  f22_.Draw();
  glPopMatrix();
}

int EllieShooting2D::OnKeyDown(SDL_Keycode key) {
  bool shot_l = false;
  if (key == SDLK_e) {
    if (shot_interval_ <= 0.0f) {
      for (int i=0; i<ARRAYSIZE(bullets_); ++i) {
        if (!bullets_[i].IsActive()) {
          if (shot_l) {
            bullets_[i].Initialize(f22_.GetShotPos(false), glm::vec2(0.0f, -200.0f));
            break;
          } else {
            bullets_[i].Initialize(f22_.GetShotPos(true), glm::vec2(0.0f, -200.0f));
            shot_l = true;
          }
        }
      }
      shot_interval_ = kShotInterval;
    }
  }
  return 0;
}
