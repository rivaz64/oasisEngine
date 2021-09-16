/**
 * @file oaBoxAABB.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#include "oaVector3f.h"
#include "oaBoxAABB.h"
#include "oaSphere.h"

bool oaEngineSDK::BoxAABB::isPointInside(const Vector3f& point)
{
  return point.x>minPoint.x && point.x < maxPoint.x &&
         point.y>minPoint.y && point.y < maxPoint.y &&
         point.z>minPoint.z && point.z < maxPoint.z;
}

bool oaEngineSDK::BoxAABB::overlap(const BoxAABB& box)
{
  return box.maxPoint.x > minPoint.x && box.minPoint.x < maxPoint.x &&
         box.maxPoint.y > minPoint.y && box.minPoint.y < maxPoint.y &&
         box.maxPoint.z > minPoint.z && box.minPoint.z < maxPoint.z;
}

bool oaEngineSDK::BoxAABB::overlapp(const Sphere& s)
{
  Vector3f point = { Math::max(minPoint.x, Math::min(s.getCenter().x, maxPoint.x)),
                     Math::max(minPoint.y, Math::min(s.getCenter().y, maxPoint.y)),
                     Math::max(minPoint.z, Math::min(s.getCenter().z, maxPoint.z)) };

  return point.len() < s.getRadius();
}
