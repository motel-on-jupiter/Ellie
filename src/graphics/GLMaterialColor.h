/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef GLMATERIALCOLOR_H_
#define GLMATERIALCOLOR_H_

struct GLMaterialColor {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;

  GLMaterialColor(const glm::vec3 &color)
      : ambient(color),
        diffuse(color),
        specular(glm::vec3(1.0f)),
        shininess(1.0f) {
  }
  GLMaterialColor(const glm::vec3 &ambient, const glm::vec3 &diffuse,
                  const glm::vec3 &specular, float shininess)
      : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {
  }
};

extern void glMaterial(GLenum face, const GLMaterialColor &material_color);

#endif /* GLMATERIALCOLOR_H_ */
