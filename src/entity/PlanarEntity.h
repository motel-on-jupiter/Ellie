/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef PLANARENTITY_H_
#define PLANARENTITY_H_

#include <boost/noncopyable.hpp>
#include "util/auxiliary/glm_aux.h"

class PlanarEntity {
 public:
  PlanarEntity(const glm::vec2 &pos, float rot, const glm::vec2 &scale) :
    pos_(pos), rot_(rot), scale_(scale) {}
  virtual ~PlanarEntity() {}

  void Move(const glm::vec2 &offset) { set_pos(pos() + offset); }
  void MoveTo(const glm::vec2 &pos) { set_pos(pos); }
  void Rotate(float offset) { set_rot(glm_aux::normalizeAngle(rot() + offset)); }
  void RotateTo(float rot) { set_rot(glm_aux::normalizeAngle(rot)); }
  void Rescale(const glm::vec2 &offset) { set_scale(scale() + offset); }
  void RescaleTo(const glm::vec2 &scale) { set_scale(scale); }

  glm::vec2 pos() const { return pos_; }
  void set_pos(const glm::vec2 &pos) { pos_ = pos; }
  float rot() const { return rot_; }
  void set_rot(float rot) { rot_ = rot; }
  glm::vec2 scale() const { return scale_; }
  void set_scale(const glm::vec2 &scale) { scale_ = scale; }

 private:
  glm::vec2 pos_;
  float rot_;
  glm::vec2 scale_;
};

class PlanarEntityMixIn : public boost::noncopyable {
 public:
  explicit PlanarEntityMixIn(PlanarEntity &entity) : entity_(entity) {}
  virtual ~PlanarEntityMixIn() {}

 protected:
  PlanarEntity &entity() { return entity_; }
  const PlanarEntity &entity() const { return entity_; }

 private:
  PlanarEntity &entity_;
};

#endif /* PLANARENTITY_H_ */
