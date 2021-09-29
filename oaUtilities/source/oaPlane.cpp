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

float 
Plane::distance(const Vector3f& p)
{
  return Math::abs(Vector3f::dot(normal,p)+d);
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
Plane::intersect(Line& l,Vector3f& point)
{
  float fv = Vector3f::dot(normal,l.getDirection());
  if (Math::abs(fv) > FLT_MIN) {
    point = l.getStaringPoint() - l.getDirection() * ((Vector3f::dot(normal,l.getStaringPoint())+d) / fv);
    return true;
  }
  return false;
}

bool 
Plane::intersect(Plane& p1, Plane& p2, Vector3f& point)
{
  Vector3f n =  Vector3f::cross(p1.normal,p2.normal);
  float det = Vector3f::dot(n,normal);
  if (det > FLT_MIN) {
    point = (Vector3f::cross(normal,p1.normal) * p2.d + Vector3f::cross(normal,p2.normal) * p1.d - n * d) / det;
    return true;
  }
  return false;
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

