/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/scene/EllieShooting2D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/wrapper/coroutine_wrap.h"
#include "util/wrapper/glgraphics_wrap.h"

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
const glm::vec2 EllieShooting2D::kBulletVelocity = glm::vec2(0.0f, -200.0f);

EllieShooting2D::EllieShooting2D()
    : EllieBaseGameScene("2D Shooting"),
      stage_(),
      f22_(),
      ufos_(),
      ccr_(nullptr),
      time_(0.0f),
      ufo_idx_(0),
      scene_pausing_(false),
      shooting_(false),
      shot_interval_(-1.0f) {
  memset(moving_, 0, sizeof(moving_));
}

EllieShooting2D::~EllieShooting2D() {
}

int EllieShooting2D::Initialize() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);
  f22_.Initialize(glm::vec2(1000.0f, 1000.0f), 0.0f);
  return 0;
}

void EllieShooting2D::Finalize() {
  for (int i=0; i<ARRAYSIZE(ufos_); ++i) {
    ufos_[i].Finalize();
  }
}

void EllieShooting2D::DirectByScript(float elapsed_time) {
  struct ccrContextTag **ccrParam = (struct ccrContextTag **) &ccr_;
  ccrBeginContext;
  ccrEndContext(ctx);
  ccrBegin_(ctx);
  ufo_idx_ = 0;
  while (ufo_idx_ < 4) {
    for (time_ = 0.3f; time_ >= 0.0f; time_ -= elapsed_time) {
      ccrReturnV;
    }
    ufos_[ufo_idx_].Initialize(glm::vec2(900.0f, 700.0f));
    ++ufo_idx_;
  }
  while (!ufos_[0].script_end()) {
    ccrReturnV;
  }
  while (ufo_idx_ < 8) {
    for (time_ = 0.3f; time_ >= 0.0f; time_ -= elapsed_time) {
      ccrReturnV;
    }
    ufos_[ufo_idx_].Initialize(glm::vec2(1100.0f, 700.0f));
    ++ufo_idx_;
  }
  while (!ufos_[4].script_end()) {
    ccrReturnV;
  }
  ccrFinishV;
}

void EllieShooting2D::Update(float elapsed_time) {
  if (!scene_pausing_) {
    DirectByScript(elapsed_time);

    for (int i = 0; i < ARRAYSIZE(bullets_); ++i) {
      bullets_[i].Update(elapsed_time);
    }
    if (moving_[0]) {
      f22_.MoveForward();
    }
    if (moving_[1]) {
      f22_.MoveBack();
    }
    if (moving_[2]) {
      f22_.MoveLeft();
    }
    if (moving_[3]) {
      f22_.MoveRight();
    }
    if (shooting_) {
      if (shot_interval_ > 0.0f) {
        shot_interval_ -= elapsed_time;
      } else {
        bool shot_l = false;
        for (int i = 0; i < ARRAYSIZE(bullets_); ++i) {
          if (!bullets_[i].IsActive()) {
            if (shot_l) {
              bullets_[i].Initialize(f22_.GetShotPos(false), kBulletVelocity);
              break;
            } else {
              bullets_[i].Initialize(f22_.GetShotPos(true), kBulletVelocity);
              shot_l = true;
            }
          }
        }
        shot_interval_ = kShotInterval;
      }
    } else {
      shot_interval_ = -1.0f;
    }
    for (int i=0; i<ARRAYSIZE(ufos_); ++i) {
      ufos_[i].Update(elapsed_time);
    }
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

  if (!scene_pausing_) {
    glMatrixMode(GL_PROJECTION);
    glm::vec2 focus_pos = glm::vec2(1000.0f, 900.0f);
    float zoom_ratio = 2.0f;
    glLoadMatrixf(
        glm::value_ptr(
            glm::ortho(focus_pos.x - window_size.x * 0.5f / zoom_ratio,
                       focus_pos.x + window_size.x * 0.5f / zoom_ratio,
                       focus_pos.y + window_size.y * 0.5f / zoom_ratio,
                       focus_pos.y - window_size.y * 0.5f / zoom_ratio, -1.0f,
                       1.0f)));
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < ARRAYSIZE(bullets_); ++i) {
      bullets_[i].Draw();
    }
    f22_.Draw();
    for (int i=0; i<ARRAYSIZE(ufos_); ++i) {
      ufos_[i].Draw();
    }
  }
  glPopMatrix();
}

void EllieShooting2D::OnKeyDown(SDL_Keycode key) {
  if (scene_pausing_) {
    switch (key) {
      case SDLK_SPACE:
        scene_pausing_ = false;
        break;
    }
  } else {
    switch (key) {
      case SDLK_w:
        moving_[0] = true;
        break;
      case SDLK_s:
        moving_[1] = true;
        break;
      case SDLK_a:
        moving_[2] = true;
        break;
      case SDLK_d:
        moving_[3] = true;
        break;
      case SDLK_e:
        shooting_ = true;
        break;
      case SDLK_SPACE:
        scene_pausing_ = true;
        break;
    }
  }
}

void EllieShooting2D::OnKeyUp(SDL_Keycode key) {
  switch (key) {
    case SDLK_w:
      moving_[0] = false;
      break;
    case SDLK_s:
      moving_[1] = false;
      break;
    case SDLK_a:
      moving_[2] = false;
      break;
    case SDLK_d:
      moving_[3] = false;
      break;
    case SDLK_e:
      shooting_ = false;
      break;
  }
}
