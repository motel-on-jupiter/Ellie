/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "scene/TitleScene.h"
#include "scene/BaseScene.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/wrapper/glgraphics_wrap.h"

TitleScene::TitleScene(const char *name)
    : BaseScene(name) {
}

TitleScene::~TitleScene() {
}

void TitleScene::Draw(const glm::vec2& window_size) {
  if (scene_time() - static_cast<float>(static_cast<int>(scene_time()))
      > 0.8f) {
    // for blinking
    return;
  }
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(
      glm::value_ptr(glm::ortho(0.0f, window_size.x, window_size.y, 0.0f)));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  static const unsigned char *notice_message =
      reinterpret_cast<const unsigned char *>("PRESS ENTER KEY");
  glm::vec2 string_size = glm::vec2(
      glutBitmapLength(GLUT_BITMAP_9_BY_15, notice_message),
      glutBitmapHeight(GLUT_BITMAP_9_BY_15));
  glRasterPos2fv(glm::value_ptr(window_size * 0.5f - string_size * 0.5f));
  glutBitmapString(GLUT_BITMAP_9_BY_15, notice_message);
  glPopMatrix();
}

void TitleScene::OnKeyDown(const SDL_KeyboardEvent &keyboard) {
  if (keyboard.keysym.sym == SDLK_RETURN) {
    set_finished(true);
  }
}

void TitleScene::OnKeyUp(const SDL_KeyboardEvent &keyboard) {
  UNUSED(keyboard);
}

void TitleScene::OnMouseButtonDown(const SDL_MouseButtonEvent &button) {
  UNUSED(button);
}

void TitleScene::OnMouseMotion(const SDL_MouseMotionEvent &motion) {
  UNUSED(motion);
}

int TitleScene::OnInitial() {
  return 0;
}

void TitleScene::OnFinal() {
}

void TitleScene::OnStep(float elapsed_time) {
  UNUSED(elapsed_time);
}

