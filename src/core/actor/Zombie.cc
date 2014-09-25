/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#include "core/actor/Zombie.h"
#include "entity/CubicEntity.h"
#include "entity/CubicEntityDraw.h"
#include "entity/CubicEntityPhysics.h"
#include "graphics/GLMaterialColor.h"
#include "util/auxiliary/glm_aux.h"
#include "util/auxiliary/math_aux.h"
#include "util/catalogue/color_sample.h"

const unsigned int Zombie::kPatience = 5;
const float Zombie::kMoveSpeed = 0.3f;
const float Zombie::kTurnSpeed = 0.7f;

Zombie::Zombie(const glm::vec3 &pos, const glm::quat &rot)
    : CubicEntity(pos, rot, glm::vec3(1.0f, 1.75f, 0.3f)),
      EntityCubeDraw(*static_cast<CubicEntity *>(this), true,
                     GLMaterialColor(X11Color::to_fvec(X11Color::kTeal))),
      CubicEntityPhysics(*static_cast<CubicEntity *>(this)),
      total_damage_(0) {
}

Zombie::~Zombie() {
}

bool Zombie::Initialize() {
  if (!CubicEntityPhysics::Initialize()) {
    return false;
  }
  total_damage_ = 0;
  return true;
}

void Zombie::Update(const glm::vec3 &player_pos, float fps) {
  glm::vec3 to_player = player_pos - pos();
  to_player.y = 0.0f;
  float to_player_dist2 = glm::length2(to_player);
  if (to_player_dist2 > glm_aux::epsilon()) {
    glm::vec3 to_player_dir = glm::normalize(to_player);
    SetVelocity(to_player_dir * kMoveSpeed);

    glm::vec3 dir = rot() * glm_aux::z_dir();
    float to_player_cos = glm::dot(to_player_dir, dir);
    bool need_to_turn;
    float turn_angle;
    if (to_player_cos > 1.0f - glm_aux::epsilon()) {
      need_to_turn = false;
    } else {
      turn_angle = kTurnSpeed;
      need_to_turn = true;
      if (to_player_cos > -1.0f + glm_aux::epsilon()) {
        need_to_turn = true;
        float to_player_angle = acos(to_player_cos) * fps;
        if (abs(to_player_angle) < turn_angle) {
          turn_angle = to_player_angle;
        }
        turn_angle *= math_aux::sign(glm::cross(to_player_dir, dir).y) * -1.0f;
      }
    }
    if (need_to_turn) {
      SetAngularVelocity(glm_aux::y_dir() * turn_angle);
    }
  }
}

void Zombie::TakeDamage() {
  ++total_damage_;
  set_material_color(GLMaterialColor(glm::lerp(X11Color::to_fvec(X11Color::kTeal), X11Color::to_fvec(X11Color::kDeepPink), static_cast<float>(total_damage_) / static_cast<float>(kPatience))));
}
