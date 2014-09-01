/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "ellie/EllieTweakerContext.h"

EllieTweakerContext::EllieTweakerContext()
    : system_actual_fps(0),
      system_time_speed(1.0f) {
}

EllieTweakerContext::~EllieTweakerContext() {
}

EllieTweakerContext tweaker_ctx;
