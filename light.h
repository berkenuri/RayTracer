#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "ray.h"
#include "material.h"

class Light {

  public:

    glm::vec3 position;

    Light();
    Light(glm::vec3 pos);
    Light(const Light& other_Light);
    ~Light();

    glm::vec3 getLightPosition();
    glm::vec4 colorShading(glm::vec3 surfacePoint, glm::vec3 surfaceNormal, glm::vec4 surfaceColor, Material material);

};
#endif
