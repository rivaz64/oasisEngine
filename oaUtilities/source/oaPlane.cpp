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

Plane::Plane(const Vector3f& A, const Vector3f& B, const Vector3f& C)
{
  normal = Vector3f::cross(B - A,C - A).normalized();
  d = -Vector3f::dot(normal,A);
}

Matrix4f
Plane::reflection()
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

bool 
Plane::intersect(Plane& p, Line& intersection)
{
  Vector3f dir = Vector3f::cross(normal,p.normal);
  intersection.setDirection(dir);
  float det = Vector3f::dot(dir,dir);
  if (det > FLT_MIN) {
    intersection.setStaringPoint((Vector3f::cross(dir,normal) * p.d + Vector3f::cross(dir,p.normal) * d) / det);
    return true;
  }
  return false;
}

}

