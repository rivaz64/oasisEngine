/**
 * @file oaSphere.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#include "oaVector3f.h"
#include "oaSphere.h"
#include "oaLine.h"

bool oaEngineSDK::Sphere::isInside(const Vector3f& point)
{
  return (center-point).len()<radius;
}

bool oaEngineSDK::Sphere::overlap(Line& l)
{
  return l.distance(center) < radius && l.getDirection().dot(center-l.getStaringPoint())<l.getLenght();
}

bool oaEngineSDK::Sphere::overlap(const Sphere& s)
{
    return (center-s.center).len()<(radius+s.radius);
}
