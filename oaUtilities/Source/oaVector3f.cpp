/**
 * @file oaVector3f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#include "oaVector2f.h"
#include "oaVector3f.h"


namespace oaEngineSDK {
const Vector3f Vector3f::RIGHT = Vector3f(1, 0, 0);
const Vector3f Vector3f::LEFT = Vector3f(-1, 0, 0);
const Vector3f Vector3f::UP = Vector3f(0, 1, 0);
const Vector3f Vector3f::DOWN = Vector3f(0, -1, 0);
const Vector3f Vector3f::FRONT = Vector3f(0, 0, 1);
const Vector3f Vector3f::BACK = Vector3f(0, 0, -1);

void Vector3f::rotate(const Quaternion& q)
{
  //q.normalize();
  Vector3f b = { q.i,q.j,q.k };
  float b2 = b.x * b.x + b.y * b.y + b.z * b.z;
  float thisdot = Vector3f::dot(*this,b);
  *this = (*this * (q.r * q.r - b2) + b * (Vector3f::dot(*this,b) * 2.0f)
           + Vector3f::cross(*this,b) * (q.r * 2.0f));
}



}


