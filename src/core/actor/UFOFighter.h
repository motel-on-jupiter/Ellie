/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef UFO_FIGHTER_H_
#define UFO_FIGHTER_H_

#include "entity/BaseEntity.h"
#include "entity/EntityDraw.h"

class UFOFighter : public BaseEntity, public EntityCircleDraw {
 public:
  UFOFighter();
  virtual ~UFOFighter();

  void Initialize(const glm::vec2 &pos);
  void Finalize();
  void Update(float elapsed_time);

  bool script_end() const { return script_end_; }

 private:
  bool script_end_;
  void *ccr_;
  float timer_;
  glm::vec2 center_;
};

#endif /* UFO_FIGHTER_H_ */
