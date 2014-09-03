/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef F22FIGHTER_H_
#define F22FIGHTER_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class F22Fighter : public BaseEntity, public EntityTriangleDraw {
 public:
  F22Fighter();
  virtual ~F22Fighter();

  void Initialize(const glm::vec2 &pos, float rot);
};

#endif /* F22FIGHTER_H_ */
