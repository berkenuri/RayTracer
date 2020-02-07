#ifndef __OBJECT_CPP__
#define __OBJECT_CPP__

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

#include "object.h"

Object::Object() {}

Object::~Object() {}

glm::vec3 Object::getPosition() {}
glm::vec3 Object::getNormal(Ray& Ray) {}
glm::vec4 Object::getColor() {}
Material Object::getMaterial() {}
bool Object::intersected(Ray& Ray) {}
float Object::intersection(Ray& Ray) {}
glm::vec3 Object::getIntersectionCoordinate(Ray& Ray) {}
bool Object::isPlane() {}

Plane::Plane() {}

Plane::~Plane() {}

Plane::Plane(const Plane& other_Plane) {
    position = other_Plane.position;
    normal = other_Plane.normal;
    color = other_Plane.color;
    material = other_Plane.material;
}

Plane::Plane(glm::vec3 pos, glm::vec3 n, glm::vec4 c, Material& m) {
  position = pos;
  normal = glm::normalize(n);
  color = c;
  material = m;
}

glm::vec3 Plane::getPosition() {
  return position;
}

glm::vec3 Plane::getNormal(Ray& Ray) {
  return glm::normalize(normal);
}

glm::vec4 Plane::getColor() {
  return color;
}

Material Plane::getMaterial() {
  return material;
}

bool Plane::isPlane() {
  return true;
}

float Plane::intersection(Ray& Ray) {

  float dDotN = glm::dot(Ray.getDirection(), this->getNormal(Ray));
  glm::vec3 aMinusP = this->getPosition() - Ray.getOrigin();

  if (dDotN == 0.0f)
    return 0;

  float t = glm::dot(aMinusP, this->getNormal(Ray)) / dDotN;

  return t;

}

glm::vec3 Plane::getIntersectionCoordinate(Ray& Ray) {

  float t = this->intersection(Ray);
  glm::vec3 intersection = (t * Ray.getDirection()) + Ray.getOrigin();

  return intersection;

}

bool Plane::intersected(Ray& Ray) {

  float t = this->intersection(Ray);

  return (t > 0);
}

Sphere::Sphere() {}

Sphere::~Sphere() {}

Sphere::Sphere(const Sphere& other_Sphere) {
    position = other_Sphere.position;
    radius = other_Sphere.radius;
    color = other_Sphere.color;
    material = other_Sphere.material;
}

Sphere::Sphere(glm::vec3 pos, float r, glm::vec4 c, Material& m) {
  position = pos;
  radius = r;
  color = c;
  material = m;
}

float Sphere::getRadius() {
  return radius;
}

glm::vec3 Sphere::getCenter() {
  return position;
}

glm::vec4 Sphere::getColor() {
  return color;
}

Material Sphere::getMaterial() {
  return material;
}

bool Sphere::isPlane() {
  return false;
}

float Sphere::intersection(Ray& Ray) {

  float t = 0;

  float d_squared = glm::dot(Ray.getDirection(), Ray.getDirection());
  glm::vec3 pMinusC = Ray.getOrigin() - this->getCenter();
  float pMinusC_squared = glm::dot(pMinusC, pMinusC);

  float a = d_squared;
  float b = 2 * glm::dot(Ray.getDirection(), pMinusC);
  float c = pMinusC_squared - pow(this->getRadius(), 2);

  float discriminant = pow(b, 2) - (4 * a * c);

  if (discriminant < 0)
		return 0;

  float t1 = (-b - sqrt(discriminant)) / (2 * a);
  float t2 = (-b + sqrt(discriminant)) / (2 * a);

  if (t1 == 0)
    t = t2;
  else if (t2 == 0)
    t = t1;
  else if (t1 <= t2)
    t = t1;
  else
    t = t2;

  return t;
}

glm::vec3 Sphere::getIntersectionCoordinate(Ray& Ray) {

  float t = this->intersection(Ray);
  glm::vec3 intersection = (t * Ray.getDirection()) + Ray.getOrigin();

  return intersection;
}

bool Sphere::intersected(Ray& Ray) {

  float t = this->intersection(Ray);

  return (t > 0);
}

glm::vec3 Sphere::getNormal(Ray& Ray) {

  glm::vec3 x = this->getIntersectionCoordinate(Ray);
  glm::vec3 normal = (x - this->getCenter()) / this->getRadius();

  return normal;
}

#endif
