/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_SHOOTING_2D_H_
#define ELLIE_SHOOTING_2D_H_

#include "core/EllieGame.h"

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
};

#endif /* ELLIE_SHOOTING_2D_H_ */
