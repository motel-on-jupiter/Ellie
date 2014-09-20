/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CUBICENTITYPHYSICS_H_
#define CUBICENTITYPHYSICS_H_

#include "entity/CubicEntity.h"

class CubicEntityPhysics : public CubicEntityMixIn {
 public:
  CubicEntityPhysics(CubicEntity &entity, const glm::vec3 &velocity)
      : CubicEntityMixIn(entity),
        velocity_(velocity) {
  }
  virtual ~CubicEntityPhysics() {
  }

  void Update(float elapsed_time) {
    prev_pos_ = entity().pos();
    entity().Move(entity().rot() * velocity_ * elapsed_time);
  }

  const glm::vec3 &prev_pos() const {
    return prev_pos_;
  }
  const glm::vec3 &velocity() const {
    return velocity_;
  }

 private:
  glm::vec3 prev_pos_;
  glm::vec3 velocity_;
};

#endif /* CUBICENTITYPHYSICS_H_ */
