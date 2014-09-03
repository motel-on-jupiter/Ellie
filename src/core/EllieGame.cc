/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "EllieGame.h"

#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include "core/scene/EllieShooting2D.h"
#include "util/logging/Logger.h"
#include "util/macro_util.h"

EllieGame::EllieGame()
    : scenes_(),
      active_scene_(nullptr),
      font_(nullptr) {
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
  EllieGameSceneInterface *scene = new EllieShooting2D();
  if (scene == nullptr) {
    LOGGER.Error("Failed to create shooting 2d scene object");
  }
  scenes_.push_back(scene);
  return 0;
}

void EllieGame::Finalize() {
  if (active_scene_ != nullptr) {
    active_scene_->Finalize();
    active_scene_ = nullptr;
  }
  for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
    delete *it;
  }
  scenes_.clear();
  if (font_ != nullptr) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
}

void EllieGame::Update(float elapsed_time) {
  if (active_scene_ != nullptr) {
    active_scene_->Update(elapsed_time);
  }
}

void EllieGame::Draw(const glm::vec2 &window_size) {
  if (active_scene_ == nullptr) {
    glSetClearingColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearAll();
  } else {
    active_scene_->Draw(window_size);
  }
}

int EllieGame::OnKeyDown(SDL_Keycode key) {
  if (active_scene_ == nullptr) {
    if ((key >= SDLK_1) && (key <= SDLK_9)) {
      size_t scene_idx = static_cast<size_t>(key - SDLK_1);
      if (scene_idx < scenes_.size()) {
        LOGGER.Info("Set up the game scene");
        int ret = scenes_.at(scene_idx)->Initialize();
        if (ret < 0) {
          LOGGER.Error("Failed to setup the scene (ret: %d, scene: %d)", ret,
                       scene_idx);
          return -1;
        }
        active_scene_ = scenes_.at(scene_idx);
      }
    }
  } else {
    switch (key) {
      case SDLK_0:
        LOGGER.Info("Clean up the current scene");
        active_scene_->Finalize();
        active_scene_ = nullptr;
        break;
      case SDLK_w:
      case SDLK_a:
      case SDLK_s:
      case SDLK_d:
      case SDLK_e:
        active_scene_->OnKeyDown(key);
        break;
    }
  }
  return 0;
}

void EllieGame::OnKeyUp(SDL_Keycode key) {
  if (active_scene_ != nullptr) {
    switch (key) {
      case SDLK_w:
      case SDLK_a:
      case SDLK_s:
      case SDLK_d:
      case SDLK_e:
        active_scene_->OnKeyUp(key);
        break;
    }
  }
}
