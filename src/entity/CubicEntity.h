/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CUBICENTITY_H_
#define CUBICENTITY_H_

#include <boost/noncopyable.hpp>
#include <glm/gtx/quaternion.hpp>
#include "util/auxiliary/math_aux.h"

class CubicEntity {
 public:
  CubicEntity(const glm::vec3 &pos, const glm::quat &rot,
              const glm::vec3 &scale)
      : pos_(pos),
        rot_(rot),
        scale_(scale) {
  }
  virtual ~CubicEntity() {
  }

  void Move(const glm::vec3 &offset) {
    set_pos(pos() + offset);
  }
  void MoveTo(const glm::vec3 &pos) {
    set_pos(pos);
  }
  void Rotate(const glm::quat &offset) {
    set_rot(offset * rot());
  }
  void RotateTo(const glm::quat &rot) {
    set_rot(rot);
  }
  void Rescale(const glm::vec3 &offset) {
    set_scale(scale() * offset);
  }
  void RescaleTo(const glm::vec3 &scale) {
    set_scale(scale);
  }

  const glm::vec3 &pos() const {
    return pos_;
  }
  void set_pos(const glm::vec3 &pos) {
    pos_ = pos;
  }
  const glm::quat &rot() const {
    return rot_;
  }
  void set_rot(const glm::quat &rot) {
    rot_ = rot;
  }
  const glm::vec3 &scale() const {
    return scale_;
  }
  void set_scale(const glm::vec3 &scale) {
    scale_ = scale;
  }

  const glm::mat4 &BuildTransformMatrix() const {
    return glm::translate(pos_) * glm::toMat4(rot_) * glm::scale(scale_);
  }

 private:
  glm::vec3 pos_;
  glm::quat rot_;
  glm::vec3 scale_;
};

class CubicEntityMixIn : public boost::noncopyable {
 public:
  explicit CubicEntityMixIn(CubicEntity &entity)
      : entity_(entity) {
  }
  virtual ~CubicEntityMixIn() {
  }

 protected:
  CubicEntity &entity() {
    return entity_;
  }
  const CubicEntity &entity() const {
    return entity_;
  }

 private:
  CubicEntity &entity_;
};

#endif /* CUBICENTITY_H_ */
