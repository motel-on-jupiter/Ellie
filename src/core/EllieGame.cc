/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "EllieGame.h"

#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include "core/scene/EllieShooter3D.h"
#include "core/scene/EllieShooting2D.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/logging/Logger.h"

EllieGame::EllieGame()
    : scenes_(),
      current_scene_(nullptr),
      font_(nullptr),
      cursor_(0),
      ongoing_(false) {
}

EllieGame::~EllieGame() {
  Finalize();
}

int EllieGame::Initialize() {
  font_ = TTF_OpenFont("share/ipag00303/ipag.ttf", 24);
  if (font_ == nullptr) {
    LOGGER.Error("Failed to open font with SDL_ttf (errmsg: %s)",
    TTF_GetError());
    return -1;
  }
  EllieBaseGameScene *scene = new EllieShooting2D();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create shooting 2d scene object");
  }
  scenes_.push_back(scene);
  scene = new EllieShooter3D();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create shooter 3d scene object");
  }
  scenes_.push_back(scene);
  ongoing_ = true;
  return 0;
}

void EllieGame::Finalize() {
  if (current_scene_ != nullptr) {
    current_scene_->Finalize();
    current_scene_ = nullptr;
  }
  for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
    delete *it;
  }
  scenes_.clear();
  if (font_ != nullptr) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
  ongoing_ = false;
}

void EllieGame::Update(float elapsed_time) {
  if (!ongoing_) {
    return;
  }

  if (current_scene_ != nullptr) {
    current_scene_->Update(elapsed_time);
  }
}

void EllieGame::Draw(const glm::vec2 &window_size) {
  if (!ongoing_) {
    return;
  }

  if (current_scene_ == nullptr) {
    glSetClearanceColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearAll();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(
        glm::value_ptr(glm::ortho(0.0f, window_size.x, window_size.y, 0.0f)));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec2 name_pos = glm::vec2(10.0f, 20.0f);
    unsigned int idx = 0;
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
      glRasterPos2fv(glm::value_ptr(name_pos));
      glutBitmapString(
          GLUT_BITMAP_9_BY_15,
          reinterpret_cast<const unsigned char *>((
              (idx == cursor_) ? "-> " : "   ")));
      glutBitmapString(
          GLUT_BITMAP_9_BY_15,
          reinterpret_cast<const unsigned char *>((*it)->name().c_str()));
      name_pos += glm::vec2(0.0f, 12);
      ++idx;
    }
  } else {
    current_scene_->Draw(window_size);
  }
}

int EllieGame::OnKeyDown(SDL_Keycode key) {
  if (!ongoing_) {
    return 0;
  }

  if (current_scene_ == nullptr) {
    switch (key) {
      case SDLK_j:
      case SDLK_DOWN:
        if (cursor_ < scenes_.size() - 1) {
          ++cursor_;
        }
        break;
      case SDLK_k:
      case SDLK_UP:
        if (cursor_ > 0) {
          --cursor_;
        }
        break;
      case SDLK_RETURN: {
        EllieBaseGameScene *setup_scene = scenes_.at(cursor_);
        LOGGER.Info("Set up the game scene (scene: %s)",
                    setup_scene->name().c_str());
        int ret = setup_scene->Initialize();
        if (ret < 0) {
          LOGGER.Error("Failed to setup the scene (ret: %d, scene: %s)", ret,
                       setup_scene->name().c_str());
          return -1;
        }
        current_scene_ = setup_scene;
        break;
      }
      case SDLK_ESCAPE:
        ongoing_ = false;
        break;
    }
  } else {
    switch (key) {
      case SDLK_w:
      case SDLK_a:
      case SDLK_s:
      case SDLK_d:
      case SDLK_e:
      case SDLK_SPACE:
        current_scene_->OnKeyDown(key);
        break;
      case SDLK_ESCAPE:
        current_scene_->Finalize();
        LOGGER.Info("Clean up the current scene (scene: %s)", current_scene_->name().c_str());
        current_scene_ = nullptr;
        break;
    }
  }
  return 0;
}

void EllieGame::OnKeyUp(SDL_Keycode key) {
  if (!ongoing_) {
    return;
  }

  if (current_scene_ != nullptr) {
    switch (key) {
      case SDLK_w:
      case SDLK_a:
      case SDLK_s:
      case SDLK_d:
      case SDLK_e:
      case SDLK_SPACE:
        current_scene_->OnKeyUp(key);
        break;
    }
  }
}
