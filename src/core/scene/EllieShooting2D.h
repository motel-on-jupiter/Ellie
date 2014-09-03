/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTING_2D_H_
#define ELLIE_SHOOTING_2D_H_

#include "core/actor/F22Fighter.h"
#include "core/EllieGame.h"

class EllieShooting2DStage {
 public:
  EllieShooting2DStage();
  ~EllieShooting2DStage();

  void Draw(const glm::vec2 &window_size);

 private:
  static const size_t kNumXMappingStars;
  static const size_t kNumYMappingStars;
  static const int kRatioMappingStars;

  std::vector<std::vector<bool>> star_map_;
};

class EllieShooting2D : public EllieGameSceneInterface {
 public:
  EllieShooting2D();
  virtual ~EllieShooting2D();

  virtual int Initialize(const glm::vec2 &window_size);
  virtual void Finalize();
  virtual void Update(float elapsed_time, const glm::vec2 &window_size);
  virtual void Draw(const glm::vec2 &window_size);
  virtual int OnMouseButtonDown(unsigned char button,
                                const glm::vec2 &cursor_pos);

 private:
  EllieShooting2DStage stage_;
  F22Fighter f22_;
};

#endif /* ELLIE_SHOOTING_2D_H_ */
