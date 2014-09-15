/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef PLANARENTITYDRAW_H_
#define PLANARENTITYDRAW_H_

#include <GL/glew.h>
#include "entity/PlanarEntity.h"

class PlanarEntityDraw : public PlanarEntityMixIn {
 public:
  PlanarEntityDraw(PlanarEntity &entity, const GLubyte *color)
  : PlanarEntityMixIn(entity), color_(color) {}
  virtual ~PlanarEntityDraw() {}

  virtual void Draw() const = 0;

  const GLubyte* color() const { return color_; }
  void set_color(const GLubyte* color) { color_ = color; }

 private:
  const GLubyte *color_;
};

class EntityPointDraw : public PlanarEntityDraw {
 public:
  EntityPointDraw(PlanarEntity &entity, const GLubyte *color);
  virtual ~EntityPointDraw() {}

  virtual void Draw() const;
};

class EntityCircleDraw : public PlanarEntityDraw {
 public:
  EntityCircleDraw(PlanarEntity &entity, unsigned int splits, bool fill, const GLubyte *color);
  virtual ~EntityCircleDraw() {}

  virtual void Draw() const;

  unsigned int splits() const { return splits_; }
  void set_splits(unsigned int splits) { splits_ = splits; }
  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  unsigned int splits_;
  bool fill_;
};

class EntityTriangleDraw : public PlanarEntityDraw {
 public:
  EntityTriangleDraw(PlanarEntity &entity, bool fill, const GLubyte *color);
  virtual ~EntityTriangleDraw() {}

  virtual void Draw() const;

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

class EntityRectangleDraw : public PlanarEntityDraw {
 public:
  EntityRectangleDraw(PlanarEntity &entity, bool fill, const GLubyte *color);
  virtual ~EntityRectangleDraw() {}

  virtual void Draw() const;

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

#endif /* PLANARENTITYDRAW_H_ */
