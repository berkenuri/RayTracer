#ifndef __MATERIAL_CPP__
#define __MATERIAL_CPP__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

#include "material.h"

Material::Material(std::string material) {

  if (material.compare("shiny") == 0) {

    shininess = 9;
    diffuse_coefficient = glm::vec4(0.9, 0.9, 0.9, 0);
    specular_coefficient = glm::vec4(1, 1, 1, 1);

  } else {

    shininess = 1;
    diffuse_coefficient = glm::vec4(0.4, 0.4, 0.4, 0);
    specular_coefficient = glm::vec4(0.2, 0.2, 0.2, 0);

  }

}

Material::Material() {}

Material::~Material() {}

#endif
