/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CUBICENTITYDRAW_H_
#define CUBICENTITYDRAW_H_

#include <GL/glew.h>
#include "entity/CubicEntity.h"
#include "graphics/GLMaterialColor.h"

class CubicEntityDraw : public CubicEntityMixIn {
 public:
  CubicEntityDraw(CubicEntity &entity, const GLMaterialColor &material_color)
      : CubicEntityMixIn(entity),
        material_color_(material_color) {
  }
  virtual ~CubicEntityDraw() {
  }

  virtual void Draw() const = 0;

  const GLMaterialColor &material_color() const {
    return material_color_;
  }
  void set_material_color(const GLMaterialColor &color) {
    material_color_ = color;
  }

 private:
  GLMaterialColor material_color_;
};

class EntitySphereDraw : public CubicEntityDraw {
 public:
  EntitySphereDraw(CubicEntity &entity, bool fill, int slices, int stacks,
                   const GLMaterialColor &material_color);
  virtual ~EntitySphereDraw() {
  }

  virtual void Draw() const;

  bool fill() const {
    return fill_;
  }
  void set_fill(bool fill) {
    fill_ = fill;
  }
  int slices() const {
    return slices_;
  }
  void set_slices(int slices) {
    slices_ = slices;
  }
  int stacks() const {
    return stacks_;
  }
  void set_stacks(int stacks) {
    stacks_ = stacks;
  }

 private:
  bool fill_;
  int slices_;
  int stacks_;
};

class EntityCubeDraw : public CubicEntityDraw {
 public:
  EntityCubeDraw(CubicEntity &entity, bool fill,
                 const GLMaterialColor &material_color);
  virtual ~EntityCubeDraw() {
  }

  virtual void Draw() const;

  bool fill() const {
    return fill_;
  }
  void set_fill(bool fill) {
    fill_ = fill;
  }

 private:
  bool fill_;
};

#endif /* CUBICENTITYDRAW_H_ */
