/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef ENTITYDRAW_H_
#define ENTITYDRAW_H_

#include <GL/glew.h>
#include "entity/BaseEntity.h"

class EntityDraw : public EntityMixIn {
 public:
  EntityDraw(BaseEntity &entity, const GLubyte *color)
  : EntityMixIn(entity), color_(color) {}
  virtual ~EntityDraw() {}

  virtual void Draw() const = 0;

  const GLubyte* color() const { return color_; }
  void set_color(const GLubyte* color) { color_ = color; }

 private:
  const GLubyte *color_;
};

class EntityPointDraw : public EntityDraw {
 public:
  EntityPointDraw(BaseEntity &entity, const GLubyte *color);
  virtual ~EntityPointDraw() {}

  virtual void Draw() const;
};

class EntityCircleDraw : public EntityDraw {
 public:
  EntityCircleDraw(BaseEntity &entity, unsigned int splits, bool fill, const GLubyte *color);
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

class EntityTriangleDraw : public EntityDraw {
 public:
  EntityTriangleDraw(BaseEntity &entity, bool fill, const GLubyte *color);
  virtual ~EntityTriangleDraw() {}

  virtual void Draw() const;

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

class EntityRectangleDraw : public EntityDraw {
 public:
  EntityRectangleDraw(BaseEntity &entity, bool fill, const GLubyte *color);
  virtual ~EntityRectangleDraw() {}

  virtual void Draw() const;

  bool fill() const { return fill_; }
  void set_fill(bool fill) { fill_ = fill; }

 private:
  bool fill_;
};

#endif /* ENTITYDRAW_H_ */
