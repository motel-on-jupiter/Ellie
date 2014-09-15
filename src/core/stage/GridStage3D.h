/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef GRID_STAGE_3D_H_
#define GRID_STAGE_3D_H_

class GridStage3D {
 public:
  GridStage3D(const glm::vec3 &scale, const GLubyte (&color)[3]);
  ~GridStage3D();

  void Draw();

 private:
  glm::vec3 scale_;
  GLubyte color_[3];
};

#endif /* GRID_STAGE_3D_H_ */
