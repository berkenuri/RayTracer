#ifndef __LIGHT_CPP__
#define __LIGHT_CPP__

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

// GLM
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "light.h"

Light::Light() {}

Light::Light(glm::vec3 pos) {
  position = pos;
}

Light::~Light() {}

Light::Light(const Light& other_Light) {
  position = other_Light.position;
}

glm::vec3 Light::getLightPosition() {
  return position;
}

glm::vec4 Light::colorShading(glm::vec3 surfacePoint, glm::vec3 surfaceNormal,
  glm::vec4 surfaceColor, Material material) {

  float p = material.shininess;
  glm::vec4 kd = material.diffuse_coefficient;
  glm::vec4 ks = material.specular_coefficient;
  glm::vec4 ka = surfaceColor;
  float intensity = 0.7;

  glm::vec4 ambient = ka * intensity;

  glm::vec3 lightDirection = glm::normalize(this->getLightPosition() - surfacePoint);

  glm::vec4 lambertian = ka * intensity * fmax(0, glm::dot(surfaceNormal, lightDirection));

  glm::vec3 directionToCamera = glm::normalize(glm::vec3(0, 0, 0) - surfacePoint);
  glm::vec3 h = (directionToCamera + lightDirection) /
  glm::length(directionToCamera + lightDirection);

  glm::vec4 blinn_phong = ks * pow(fmax(0, glm::dot(surfaceNormal, h)), p);

  return glm::clamp((ambient+ 2*blinn_phong + 3*lambertian) / 3, 0.0f, 1.0f);
}

#endif
