#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>


class Material {

  public:
    float shininess;
    glm::vec4 diffuse_coefficient;
    glm::vec4 specular_coefficient;

    Material(std::string material);
    Material();
    ~Material();

};

#endif
