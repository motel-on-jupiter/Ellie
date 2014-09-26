/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef GRAPH_DRIVEN_SCENE_H_
#define GRAPH_DRIVEN_SCENE_H_

#include "scene/BaseScene.h"
#include "scene/SceneGraph.h"

class GraphDrivenScene : public BaseScene {
 public:
  GraphDrivenScene(const char *name, const SceneGraph &graph);
  virtual ~GraphDrivenScene();

  virtual void Draw(const glm::vec2 &window_size);
  virtual void OnKeyDown(const SDL_KeyboardEvent &keyboard);
  virtual void OnKeyUp(const SDL_KeyboardEvent &keyboard);
  virtual void OnMouseButtonDown(const SDL_MouseButtonEvent &button);
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &motion);

 protected:
  virtual int OnInitial();
  virtual void OnFinal();
  virtual void OnStep(float elapsed_time);

  SceneGraphIterator graph_iter_;
};

#endif /* GRAPH_DRIVEN_SCENE_H_ */
