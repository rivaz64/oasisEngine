#include"oaVector3f.h"
#include "oaLine.h"
namespace oaEngineSDK {

Line::Line(Vector3f& A, Vector3f& B)
{
  startingPoint = A;
  Vector3f difference = B - A;
  direction = difference.normal();
  lenght = difference.len();
}

Vector3f Line::pointAt(float f)
{
  return startingPoint+direction*lenght*f;
}

float Line::distance(Vector3f& p)
{
  Vector3f u = p - startingPoint;
  return direction.cross(u).len();
}

float Line::distance(Line& l)
{
  Vector3f dif = l.startingPoint - startingPoint;
  float v12 = direction.dot(direction);
  float v22 = l.direction.dot(l.direction);
  float v1v2 = direction.dot(l.direction);
  float det = v1v2 * v1v2 - v12 * v22;
  if (Math::abs(det) > FLT_MIN) {
    det = 1.f / det;
    float dpvl = dif.dot(direction);
    float dpv2 = dif.dot(l.direction);
    float t1 = (v1v2 * dpv2 - v22 * dpvl)* det;
    float t2 = (v12 * dpv2 - v1v2 * dpvl) * det;
    return (dif + l.direction * t2 - direction * t1).len();
  }
  Vector3f a = dif.cross(direction);
  return (sqrt( a.dot(a) / v12));
}

}

