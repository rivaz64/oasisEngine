/**
 * @file oaLine.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */


#include "oaLine.h"

namespace oaEngineSDK {

Line::Line(Vector3f& A, Vector3f& B)
{
  startingPoint = A;
  Vector3f difference = B - A;
  direction = difference.normalized();
  lenght = difference.magnitud();
}

Vector3f 
Line::pointAt(float f)
{
  return startingPoint+direction*lenght*f;
}

float 
Line::distance(Line& l)
{
  auto dif = l.startingPoint - startingPoint;
  float v12 = Vector3f::dot(direction,direction);
  float v22 = Vector3f::dot(l.direction,l.direction);
  float v1v2 = Vector3f::dot(direction,l.direction);
  float det = v1v2 * v1v2 - v12 * v22;
  if (Math::abs(det) > FLT_MIN) {
    det = 1.f / det;
    float dpvl = Vector3f::dot(dif,direction);
    float dpv2 = Vector3f::dot(dif,l.direction);
    float t1 = (v1v2 * dpv2 - v22 * dpvl)* det;
    float t2 = (v12 * dpv2 - v1v2 * dpvl) * det;
    return (dif + l.direction * t2 - direction * t1).magnitud();
  }
  Vector3f a = Vector3f::cross(dif,direction);
  return (sqrt( Vector3f::dot(a,a) / v12));
}

}

