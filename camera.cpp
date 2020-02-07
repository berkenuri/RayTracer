#ifndef __CAMERA_CPP__
#define __CAMERA_CPP__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <cmath>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

#include "camera.h"
#include "ray.h"

Camera::Camera() {}

Camera::Camera(std::string v, glm::vec3 pos, float focal_length, float theta_val, float width, float height) {

  view = v;
  position = pos;
  d = focal_length;
  theta = theta_val;
  w = width;
  h = height;
  aspectRatio = w/h;

  if (v.compare("perspective") == 0) {

    t = focal_length * tan(theta_val / 2);
    b = -t;
    r = t * aspectRatio;
    l = -r;

  } else {

    t = h / 2;
    b = -t;
    r = w /2;
    l = -r;
  }

}

Camera::~Camera() {}

Ray Camera::makePerspectiveViewRay(float i, float j) {

  float sigma = this->b + ((this->t - this->b) * (j + 0.5) / this->h);
  float tau = this->l + ((this->r - this->l) * (i + 0.5) / this->w);

  glm::vec3 target = (this->d * glm::vec3(0.0f, 0.0f, -1.0f)) +
  (tau * glm::vec3(1.0f, 0.0f, 0.0f)) + (sigma * glm::vec3(0.0f, 1.0f, 0.0f));

  glm::vec3 direction = glm::normalize(target);

  return Ray(position, direction);

}

Ray Camera::makeParallelViewRay(float i, float j) {

  float sigma = this->b + ((this->t - this->b) * (j + 0.5) / this->h);
  float tau = this->l + ((this->r - this->l) * (i + 0.5) / this->w);

  glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 origin = position + (tau * glm::vec3(1.0f, 0.0f, 0.0f)) +
  (sigma * glm::vec3(0.0f, 1.0f, 0.0f));

  return Ray(origin, direction);
}

std::string Camera::getCameraView() {
  return view;
}

#endif
