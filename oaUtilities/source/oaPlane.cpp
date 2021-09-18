/**
 * @file oaPlane.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#include "oaVector3f.h"
#include "oaVector4f.h"
#include "oaMatrix4f.h"
#include "oaLine.h"
#include "oaPlane.h"

namespace oaEngineSDK {

Plane::Plane(Vector3f& A, Vector3f& B, Vector3f& C)
{
  normal = (B - A).cross(C - A).normal();
  d = -normal.dot(A);
}

float Plane::distance(Vector3f& p)
{
  return Math::abs(normal.dot(p)+d);
}

Matrix4f Plane::reflection()
{
  float xy = -2.f*normal.x * normal.y;
  float xz = -2.f * normal.x * normal.z;
  float yz = -2.f * normal.y * normal.z;
  return Matrix4f(
    1.f-2.f*normal.x*normal.x,xy,xz,-2.f*normal.x*d,
    xy,1.f - 2.f * normal.y * normal.y, yz,-2.f * normal.y*d,
    xz,yz,1.f - 2.f * normal.z * normal.z,-2.f * normal.z*d ,
    0.f,0.f,0.f,1.f
    );
}

bool Plane::intersect(Line& l,Vector3f& point)
{
  float fv = normal.dot(l.getDirection());
  if (Math::abs(fv) > FLT_MIN) {
    point = l.getStaringPoint() - l.getDirection() * ((normal.dot(l.getStaringPoint())+d) / fv);
    return true;
  }
  return false;
}

bool Plane::intersect(Plane& p1, Plane& p2, Vector3f& point)
{
  auto n = p1.normal.cross(p2.normal);
  float det = n.dot(normal);
  if (det > FLT_MIN) {
    point = (normal.cross(p1.normal) * p2.d + normal.cross(p2.normal) * p1.d - n * d) / det;
    return true;
  }
  return false;
}

bool Plane::intersect(Plane& p, Line& intersection)
{
  auto dir = normal.cross(p.normal);
  intersection.setDirection(dir);
  float det = dir.dot(dir);
  if (det > FLT_MIN) {
    intersection.setStaringPoint((dir.cross(normal) * p.d + dir.cross(p.normal) * d) / det);
    return true;
  }
  return false;
}

}

