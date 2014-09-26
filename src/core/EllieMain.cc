/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "EllieMain.h"

#include <algorithm>
#include <sstream>
#include <mmsystem.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include "core/EllieGame.h"
#include "core/EllieTweakerContext.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/logging/Logger.h"
#include "util/measurement/FPSCounter.h"
#include "util/wrapper/glgraphics_wrap.h"

static const std::string kWindowCaption = "Ellie - The Motel on Jupiter";
static const Uint32 kWindowWidth = 800;
static const Uint32 kWindowHeight = 600;
static const Uint32 kIdealFrameRate = 60;

static const glm::vec2 kWindowSize = glm::vec2(kWindowWidth, kWindowHeight);
static const int kGameLoopInterval = 1000 / kIdealFrameRate;
static const float kGameLoopIntervalSec = 1.0f / kIdealFrameRate;
static const int kFPSCountSamplingTime = 1000;

static SDL_Window *window = nullptr;
static SDL_GLContext context = nullptr;
static TwBar *tw_bar = nullptr;
static EllieGame game;
static FPSCounter fps_counter(kFPSCountSamplingTime);

static void EllieCleanUp();

int EllieMain() {
  LOGGER.Info("Set up the application");

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOGGER.Error("Failed to initialize SDL video system (errmsg: %s)",
                 SDL_GetError());
    return -1;
  }

  // Initialize TTF font drawing library
  if (TTF_Init() != 0) {
    LOGGER.Error("Failed to initialize SDL_ttf (errmsg: %s)", TTF_GetError());
    EllieCleanUp();
    return -1;
  }

  // Enable double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Create the window
  window = SDL_CreateWindow(kWindowCaption.c_str(), SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED,
                            kWindowWidth, kWindowHeight, SDL_WINDOW_OPENGL);
  if (window == nullptr) {
    LOGGER.Error("Failed to create SDL window (errmsg: %s)", SDL_GetError());
    EllieCleanUp();
    return -1;
  }

  // Create OpenGL context
  context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    LOGGER.Error("Failed to create SDL context for OpenGL (errmsg: %s)",
                 SDL_GetError());
    EllieCleanUp();
    return -1;
  }

  // Initialize the GLEW (for shader support)
  GLenum glew_error = glewInit();
  if (glew_error != GLEW_OK) {
    LOGGER.Error("Failed to initialize glew library (errmsg: %s)",
                 glewGetErrorString(glew_error));
    EllieCleanUp();
    return -1;
  }

  // Initialize the GLUT (for bitmap font support)
  int glut_argc = 0;
  glutInit(&glut_argc, {});

  // Initialize global flag for Bullet
  gDisableDeactivation = true;

  // Initialize the tweaker library
  if (TwInit(TW_OPENGL, NULL) == 0) {
    LOGGER.Error("Failed to initialize the tweaker library (errmsg: %s)",
                 TwGetLastError());
    EllieCleanUp();
    return -1;
  }
  if (TwWindowSize(kWindowWidth, kWindowHeight) == 0) {
    LOGGER.Error("Failed to set the window size to tweaker (errmsg: %s)",
                 TwGetLastError());
    EllieCleanUp();
    return -1;
  }
  tw_bar = TwNewBar("TweakMenu");
  std::stringstream tw_def;
  tw_def << "TweakMenu position='" << 550 << " " << 10 << "' size='" << 240
         << " " << 580 << "' color='41 126 231' iconified=true";
  TwDefine(tw_def.str().c_str());
  if (TwAddVarRO(tw_bar, "SYSTEM_ACTUAL_FRAME_RATE", TW_TYPE_INT8,
                 &(tweaker_ctx.system_actual_fps),
                 "group='System' label='Actual Frame Rate'") == 0) {
    LOGGER.Warn("Failed to add a tweak variable for actual-FPS (errmsg: %s)",
                TwGetLastError());
  }
  if (TwAddVarRW(
      tw_bar, "SYSTEM_TIME_SPEED", TW_TYPE_FLOAT,
      &(tweaker_ctx.system_time_speed),
      "group='System' label='Time Speed' min='0' max='30' step='0.5'") == 0) {
    LOGGER.Warn("Failed to add a tweak variable for time-speed (errmsg: %s)",
                TwGetLastError());
  }

  // Initialize the game
  int ret = game.Initialize();
  if (ret < 0) {
    LOGGER.Error("Failed to initialize the game objects (ret: %d)");
    EllieCleanUp();
    return -1;
  }

  // Set the minimum timer resolution
  timeBeginPeriod(1);

  // Execute the mainloop
  int loop_stat = 0;
  while (true) {
    int start_tick = SDL_GetTicks();

    // check event
    bool escape_loop = false;
    SDL_Event event;
    while (SDL_PollEvent(&event) == 1) {
      if (TwEventSDL20(&event) != 0) {
        continue;
      }
      switch (event.type) {
        case SDL_QUIT:
          escape_loop = true;
          break;
        case SDL_KEYDOWN:
          game.OnKeyDown(event.key);
          break;
        case SDL_KEYUP:
          game.OnKeyUp(event.key);
          break;
        case SDL_MOUSEBUTTONDOWN:
          game.OnMouseButtonDown(event.button);
          break;
        case SDL_MOUSEMOTION:
          game.OnMouseMotion(event.motion);
          break;
      }
    }
    if (escape_loop || !game.on_going()) {
      break;
    }

    // Update the game
    game.Step(kGameLoopIntervalSec * tweaker_ctx.system_time_speed);

    // Draw the objects
    game.Draw(kWindowSize);
    if (TwDraw() == 0) {
      LOGGER.Error("Failed to draw the tweaker (errmsg: %s)", TwGetLastError());
      loop_stat = -1;
      break;
    }
    SDL_GL_SwapWindow(window);

    int finish_tick = SDL_GetTicks();
    int exec_tick = finish_tick - start_tick;
    Sleep(std::max<int>(kGameLoopInterval - exec_tick, 1));

    fps_counter.Update(SDL_GetTicks());
    tweaker_ctx.system_actual_fps = fps_counter.fps();
  }

  // Reset the minimum timer resolution
  timeEndPeriod(1);

  EllieCleanUp();
  return loop_stat;
}

static void EllieCleanUp() {
  LOGGER.Info("Clean up the application");

  game.Finalize();
  if (TwRemoveAllVars(tw_bar) == 0) {
    LOGGER.Warn("Failed to remove all tweaker varibables (errmsg: %s)",
                TwGetLastError());
  }
  if (TwTerminate() == 0) {
    // Ignore the error to terminate the tweaker
    // because the tweaker library may be not initialized
  }
  if (context != nullptr) {
    SDL_GL_DeleteContext(context);
  }
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
  TTF_Quit();
  SDL_Quit();
}
