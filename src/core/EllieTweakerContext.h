/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef ELLIE_TWEAKER_CONTEXT_H_
#define ELLIE_TWEAKER_CONTEXT_H_

struct EllieTweakerContext {
  int system_actual_fps;
  float system_time_speed;

  EllieTweakerContext();
  ~EllieTweakerContext();
};

extern EllieTweakerContext tweaker_ctx;

#endif /* ELLIE_TWEAKER_CONTEXT_H_ */
