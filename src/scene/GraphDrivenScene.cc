/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "scene/GraphDrivenScene.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/logging/Logger.h"

GraphDrivenScene::GraphDrivenScene(const char *name, const SceneGraph &graph)
    : BaseScene(name),
      graph_iter_(graph) {
}

GraphDrivenScene::~GraphDrivenScene() {
}

void GraphDrivenScene::Draw(const glm::vec2 &window_size) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->Draw(window_size);
  }
}

void GraphDrivenScene::OnKeyDown(const SDL_KeyboardEvent &keyboard) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->OnKeyDown(keyboard);
  }
}

void GraphDrivenScene::OnKeyUp(const SDL_KeyboardEvent &keyboard) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->OnKeyUp(keyboard);
  }
}

void GraphDrivenScene::OnMouseButtonDown(const SDL_MouseButtonEvent &button) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->OnMouseButtonDown(button);
  }
}

void GraphDrivenScene::OnMouseMotion(const SDL_MouseMotionEvent &motion) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->OnMouseMotion(motion);
  }
}

int GraphDrivenScene::OnInitial() {
  if (!graph_iter_.Initiaize()) {
    LOGGER.Error("Failed to initialize graph iterator");
    return -1;
  }
  return 0;
}

void GraphDrivenScene::OnFinal() {
  graph_iter_.Finalize();
}

void GraphDrivenScene::OnStep(float elapsed_time) {
  if (graph_iter_.current() != nullptr) {
    graph_iter_.current()->Step(elapsed_time);
    if (graph_iter_.current()->finished()) {
      std::string prev_name = graph_iter_.current()->name();
      if (graph_iter_.Next(0)) {
        if (graph_iter_.current() == nullptr) {
          LOGGER.Info("Shift the scene (prev: %s, next: %s)", prev_name.c_str(),
                      SAFE_STR(graph_iter_.current()->name().c_str()));
        }
      } else {
        LOGGER.Error("Failed to next the scene graph iterator");
      }
    }
  }
}

