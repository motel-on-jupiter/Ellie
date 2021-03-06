/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef SDL_WRAP_H_
#define SDL_WRAP_H_

#include "util/wrapper/glgraphics_wrap.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#undef WIN32_LEAN_AND_MEAN
#include <SDL_opengl.h>

#include <SDL_ttf.h>
#include "util/wrapper/glm_wrap.h"
extern int RenderTTFText(TTF_Font *Font, const SDL_Color& Color,
                         const glm::vec2 &Position, const char *Text);

#endif /* SDL_WRAP_H_ */
