#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

#include "ray.h"


class Camera {

public:

  std::string view;
  glm::vec3 position;
  float d;
  float theta;
  float l;
  float r;
  float t;
  float b;
  float aspectRatio;
  float w;
  float h;

  Camera();
  Camera(std::string view, glm::vec3 pos, float focal_length, float theta_val, float width, float height);
  ~Camera();

  Ray makePerspectiveViewRay(float i, float j);
  Ray makeParallelViewRay(float i, float j);
  std::string getCameraView();


};

#endif
