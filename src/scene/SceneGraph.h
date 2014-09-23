/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef SCENE_GRAPH_H_
#define SCENE_GRAPH_H_

#include <utility>
#include <vector>
#include <boost/noncopyable.hpp>

class BaseScene;

typedef std::pair<BaseScene *, BaseScene *> SceneFlow;
typedef std::pair<SceneFlow, int> SceneEdge;
typedef std::vector<SceneEdge> SceneGraph;

class SceneGraphIterator : boost::noncopyable {
 public:
  SceneGraphIterator(const SceneGraph &graph)
      : graph_(graph),
        current_(nullptr) {
  }
  virtual ~SceneGraphIterator() {
  }

  bool Initiaize();
  void Finalize();
  bool Next(int condition);

  const SceneGraph &graph() const {
    return graph_;
  }
  BaseScene *current() {
    return current_;
  }

 private:
  void CleanCurrent();
  bool NextImpl(BaseScene *previous, int condition);

  const SceneGraph &graph_;
  BaseScene *current_;
};

#endif /* SCENE_GRAPH_H_ */
