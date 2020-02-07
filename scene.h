#ifndef __SCENE_H__
#define __SCENE_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

// GL
#define GL_GLEXT_PROTOTYPES
#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>
#endif

// STL
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>
#include <vector>

#include "object.h"
#include "camera.h"
#include "light.h"


class Scene {

  public:

    Camera camera = Camera();
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    Scene();
    ~Scene();

    void addObject(std::shared_ptr<Object> object);
    void addLight(std::shared_ptr<Light> light);
    void addCamera(Camera& cam);
    void rayTracer(std::unique_ptr<glm::vec4[]> & frame, int pixelX, int pixelY);
    glm::vec4 trace(Ray& ray, int bounce_Count);

};

#endif
