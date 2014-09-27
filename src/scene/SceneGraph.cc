/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "scene/BaseScene.h"
#include "scene/SceneGraph.h"
#include "auxiliary/csyntax_aux.h"
#include "logging/Logger.h"

bool SceneGraphIterator::Initiaize() {
  return NextImpl(nullptr, -1);
}

void SceneGraphIterator::Finalize() {
  CleanCurrent();
}

bool SceneGraphIterator::Next(int condition) {
  BaseScene *previous = current_;
  CleanCurrent();
  return NextImpl(previous, condition);
}

void SceneGraphIterator::CleanCurrent() {
  if (current_ != nullptr) {
    current_->Finalize();
  }
  current_ = nullptr;
}

bool SceneGraphIterator::NextImpl(BaseScene *previous, int condition) {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    SceneFlow flow = (*it).first;
    if ((flow.first == previous)
        && ((condition < 0) || ((*it).second == condition))) {
      BaseScene *next = flow.second;
      if (next == nullptr) {
        LOGGER.Warn("Ignored the invalid scene flow whose end is null");
        continue;
      }
      int ret = next->Initialize();
      if (ret < 0) {
        LOGGER.Error("Failed to initialize the scene (scene: %s, error: %d)",
                     next->name().c_str(), ret);
        return false;
      }
      current_ = next;
    }
  }
  return true;
}
