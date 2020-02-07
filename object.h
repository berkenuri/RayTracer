#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "ray.h"
#include "material.h"

class Object {

  public:

    glm::vec3 position;
    glm::vec4 color;
    Material material = Material();

    Object();
    ~Object();

    virtual glm::vec3 getPosition();
    virtual glm::vec3 getNormal(Ray& Ray);
    virtual glm::vec4 getColor();
    virtual Material getMaterial();
    virtual bool intersected(Ray& Ray);
    virtual float intersection(Ray& Ray);
    virtual glm::vec3 getIntersectionCoordinate(Ray& Ray);
    virtual bool isPlane();

};

class Plane : public Object {

  public:

    glm::vec3 normal;

    Plane();
    Plane(const Plane& other_Plane);
    Plane(glm::vec3 pos, glm::vec3 n, glm::vec4 c, Material& m);
    ~Plane();

    glm::vec3 getPosition();
    glm::vec3 getNormal(Ray& Ray);
    glm::vec4 getColor();
    Material getMaterial();
    bool intersected(Ray& Ray);
    float intersection(Ray& Ray);
    glm::vec3 getIntersectionCoordinate(Ray& Ray);
    bool isPlane();

};

class Sphere : public Object {

  public:

    float radius;

    Sphere();
    Sphere(const Sphere& other_Sphere);
    Sphere(glm::vec3 pos, float r, glm::vec4 c, Material& m);
    ~Sphere();

    float getRadius();
    glm::vec3 getCenter();
    glm::vec4 getColor();
    Material getMaterial();
    bool intersected(Ray& Ray);
    float intersection(Ray& Ray);
    glm::vec3 getIntersectionCoordinate(Ray& Ray);
    glm::vec3 getNormal(Ray& Ray);
    bool isPlane();

};

#endif
