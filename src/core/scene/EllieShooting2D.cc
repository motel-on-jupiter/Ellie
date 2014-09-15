/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/scene/EllieShooting2D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/catalogue/color_sample.h"
#include "util/logging/Logger.h"
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

EllieShooting2DTitle::EllieShooting2DTitle()
    : EllieBaseGameScene("Title") {
}

EllieShooting2DTitle::~EllieShooting2DTitle() {
}

void EllieShooting2DTitle::Draw(const glm::vec2& window_size) {
  if (scene_time() - static_cast<float>(static_cast<int>(scene_time()))
      < 0.8f) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    static const unsigned char *notice_message =
        reinterpret_cast<const unsigned char *>("PRESS ENTER KEY");
    glm::vec2 string_size = glm::vec2(
        glutBitmapLength(GLUT_BITMAP_9_BY_15, notice_message),
        glutBitmapHeight(GLUT_BITMAP_9_BY_15));
    glRasterPos2fv(glm::value_ptr(window_size * 0.5f - string_size * 0.5f));
    glutBitmapString(GLUT_BITMAP_9_BY_15, notice_message);
  }
}

void EllieShooting2DTitle::OnKeyDown(SDL_Keycode key) {
  if (key == SDLK_RETURN) {
    set_finished(true);
  }
}

void EllieShooting2DTitle::OnKeyUp(SDL_Keycode key) {
  UNUSED(key);
}

int EllieShooting2DTitle::OnInitial() {
  return 0;
}

void EllieShooting2DTitle::OnFinal() {
}

void EllieShooting2DTitle::OnUpdate(float elapsed_time) {
  UNUSED(elapsed_time);
}

const float EllieShooting2DIngame::kShotInterval = 0.1f;
const glm::vec2 EllieShooting2DIngame::kBulletVelocity = glm::vec2(0.0f,
                                                                   -200.0f);

EllieShooting2DIngame::EllieShooting2DIngame()
    : EllieBaseGameScene("Ingame"),
      f22_(),
      ufos_(),
      ccrParam_(nullptr),
      time_(0.0f),
      ufo_idx_(0),
      scene_pausing_(false),
      shooting_(false),
      shot_interval_(-1.0f) {
  memset(moving_, 0, sizeof(moving_));
}

EllieShooting2DIngame::~EllieShooting2DIngame() {
}

void EllieShooting2DIngame::DirectEnemies(float elapsed_time) {
  ccrAsContParam(ccrParam_);
  ccrBeginContext
    ;
  ccrEndContext(ctx);
  ccrBegin_(ctx)
  ;
  ufo_idx_ = 0;
  while (ufo_idx_ < 4) {
    for (time_ = 0.3f; time_ >= 0.0f; time_ -= elapsed_time) {
      ccrReturnV
      ;
    }
    ufos_[ufo_idx_].Initialize(glm::vec2(900.0f, 700.0f));
    ++ufo_idx_;
  }
  while (!ufos_[0].script_end()) {
    ccrReturnV
    ;
  }
  while (ufo_idx_ < 8) {
    for (time_ = 0.3f; time_ >= 0.0f; time_ -= elapsed_time) {
      ccrReturnV
      ;
    }
    ufos_[ufo_idx_].Initialize(glm::vec2(1100.0f, 700.0f));
    ++ufo_idx_;
  }
  while (!ufos_[4].script_end()) {
    ccrReturnV
    ;
  }
ccrFinishV;
}

void EllieShooting2DIngame::Draw(const glm::vec2 &window_size) {
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
    for (int i = 0; i < ARRAYSIZE(ufos_); ++i) {
      ufos_[i].Draw();
    }
  }
}

void EllieShooting2DIngame::OnKeyDown(SDL_Keycode key) {
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

void EllieShooting2DIngame::OnKeyUp(SDL_Keycode key) {
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

int EllieShooting2DIngame::OnInitial() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);
  f22_.Initialize(glm::vec2(1000.0f, 1000.0f), 0.0f);
  return 0;
}

void EllieShooting2DIngame::OnFinal() {
  for (int i = 0; i < ARRAYSIZE(ufos_); ++i) {
    ufos_[i].Finalize();
  }
  ccrAbort(ccrParam_);
}

void EllieShooting2DIngame::OnUpdate(float elapsed_time) {
  if (!scene_pausing_) {
    DirectEnemies(elapsed_time);

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
    for (int i = 0; i < ARRAYSIZE(ufos_); ++i) {
      ufos_[i].Update(elapsed_time);
    }
  }
}

EllieShooting2D::EllieShooting2D()
    : EllieBaseGameScene("2D Shooting"),
      stage_(),
      sub_scenes_(),
      current_scene_(nullptr) {
}

EllieShooting2D::~EllieShooting2D() {
}

void EllieShooting2D::Draw(const glm::vec2 &window_size) {
  glClearAll();

  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(glm::ortho(0.0f, window_size.x, window_size.y, 0.0f)));
  glMatrixMode(GL_MODELVIEW);
  stage_.Draw(window_size);

  if (current_scene_ != nullptr) {
    current_scene_->Draw(window_size);
  }
  glPopMatrix();
}

void EllieShooting2D::OnKeyDown(SDL_Keycode key) {
  if (current_scene_ != nullptr) {
    current_scene_->OnKeyDown(key);
  }
}

void EllieShooting2D::OnKeyUp(SDL_Keycode key) {
  if (current_scene_ != nullptr) {
    current_scene_->OnKeyUp(key);
  }
}

int EllieShooting2D::OnInitial() {
  glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);

  EllieBaseGameScene *sub_scene = new EllieShooting2DTitle();
  if (sub_scene == nullptr) {
    LOGGER.Error("Failed to allocate for sub scene object");
    return -1;
  }
  typedef std::map<std::string, EllieBaseGameScene *>::value_type SubScenesItem;
  sub_scenes_.insert(SubScenesItem(sub_scene->name(), sub_scene));

  LOGGER.Info("Set up the sub scene (scene: %s)", sub_scene->name().c_str());
  int ret = sub_scene->Initialize();
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the sub scene (scene: %s)",
                 sub_scene->name().c_str());
    delete sub_scene;
    return -1;
  }
  current_scene_ = sub_scene;

  sub_scene = new EllieShooting2DIngame();
  if (sub_scene == nullptr) {
    LOGGER.Error("Failed to allocate for sub scene object");
    return -1;
  }
  sub_scenes_.insert(SubScenesItem(sub_scene->name(), sub_scene));

  return 0;
}

void EllieShooting2D::OnFinal() {
  if (current_scene_ != nullptr) {
    current_scene_->Finalize();
    LOGGER.Info("Clean up the current sub scene (scene: %s)",
                current_scene_->name().c_str());
    current_scene_ = nullptr;
  }
  for (auto it = sub_scenes_.begin(); it != sub_scenes_.end(); ++it) {
    delete it->second;
  }
  sub_scenes_.clear();
}

void EllieShooting2D::OnUpdate(float elapsed_time) {
  struct SceneEdge {
    std::string start;
    std::string end;
  };
  static const SceneEdge kSceneGraph[] = { { "Title", "Ingame" }, };

  if (current_scene_ != nullptr) {
    current_scene_->Update(elapsed_time);

    if (current_scene_->finished()) {
      current_scene_->Finalize();
      LOGGER.Info("Clean up the current sub scene (scene: %s)",
                  current_scene_->name().c_str());
      EllieBaseGameScene *prev_scene_ = current_scene_;
      current_scene_ = nullptr;

      for (int i = 0; i < ARRAYSIZE(kSceneGraph); ++i) {
        if (kSceneGraph[i].start == prev_scene_->name()) {
          EllieBaseGameScene *sub_scene = sub_scenes_.at(kSceneGraph[i].end);

          LOGGER.Info("Set up the next sub scene (scene: %s)",
                      sub_scene->name().c_str());
          int ret = sub_scene->Initialize();
          if (ret < 0) {
            LOGGER.Error(
                "Failed to initialize next sub scene (scene: %s, error: %d)",
                current_scene_->name().c_str(), ret);
          }
          current_scene_ = sub_scene;
        }
      }
    }
  }
}

