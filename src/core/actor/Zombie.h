/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"

class Zombie : public CubicEntity, public EntityCubeDraw {
 public:
  Zombie();
  virtual ~Zombie();
};

#endif /* ZOMBIE_H_ */
