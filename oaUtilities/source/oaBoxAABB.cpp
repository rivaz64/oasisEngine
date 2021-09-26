/**
 * @file oaBoxAABB.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */


#include "oaBoxAABB.h"
#include "oaSphere.h"
namespace oaEngineSDK{
BoxAABB::BoxAABB(const Vector3f& A, const Vector3f& B)
{
  minPoint = { Math::min(A.x,B.x),Math::min(A.y,B.y) ,Math::min(A.z,B.z) };
  maxPoint = { Math::max(A.x,B.x),Math::max(A.y,B.y) ,Math::max(A.z,B.z) };
}

bool 
BoxAABB::isPointInside(const Vector3f& point)
{
  return point.x>minPoint.x && point.x < maxPoint.x &&
    point.y>minPoint.y && point.y < maxPoint.y &&
    point.z>minPoint.z && point.z < maxPoint.z;
}

bool 
BoxAABB::overlap(const BoxAABB& box)
{
  return box.maxPoint.x > minPoint.x && box.minPoint.x < maxPoint.x &&
    box.maxPoint.y > minPoint.y && box.minPoint.y < maxPoint.y &&
    box.maxPoint.z > minPoint.z && box.minPoint.z < maxPoint.z;
}

bool 
BoxAABB::overlap(const Sphere& s)
{
  Vector3f point = { Math::max(minPoint.x, Math::min(s.getCenter().x, maxPoint.x)),
    Math::max(minPoint.y, Math::min(s.getCenter().y, maxPoint.y)),
    Math::max(minPoint.z, Math::min(s.getCenter().z, maxPoint.z)) };

  return (point- s.getCenter()).magnitud() < s.getRadius();
}

}
