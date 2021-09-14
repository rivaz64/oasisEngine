#include "oaVector3f.h"
#include"oaVector4f.h"
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
    {1.f-2.f*normal.x*normal.x,xy,xz,-2.f*normal.x*d},
    {xy,1.f - 2.f * normal.y * normal.y, yz,-2.f * normal.y*d},
    {xz,yz,1.f - 2.f * normal.z * normal.z,-2.f * normal.z*d },
    {0.f,0.f,0.f,1.f}
    );
}

bool Plane::intersect(Line& l,Vector3f& point)
{
  float fv = normal.dot(l.getDirection());
  if (Math::abs(fv) > FLT_MIN) {
    point = l.getStaringPoint() - l.getDirection() * normal.dot(l.getStaringPoint() / fv);
    return true;
  }
  return false;
}

}

