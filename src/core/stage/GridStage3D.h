/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef GRID_STAGE_3D_H_
#define GRID_STAGE_3D_H_

class GridStage3D {
 public:
  GridStage3D(const glm::vec3 &scale);
  ~GridStage3D();

  void Draw();

 private:
  glm::vec3 scale_;
};

#endif /* GRID_STAGE_3D_H_ */
