/**
 * @file oaBoxAABB.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#include "oaAABB.h"

namespace oaEngineSDK{

Vector<Vector3f> 
AABB::getPoints() const
{
  Vector<Vector3f> points;
  points.resize(8);

  points[0] = minPoint;
  points[1] = Vector3f(maxPoint.x,minPoint.y,minPoint.z);
  points[2] = Vector3f(minPoint.x,maxPoint.y,minPoint.z);
  points[3] = Vector3f(minPoint.x,minPoint.y,maxPoint.z);
  points[4] = Vector3f(minPoint.x,maxPoint.y,maxPoint.z);
  points[5] = Vector3f(maxPoint.x,minPoint.y,maxPoint.z);
  points[6] = Vector3f(maxPoint.x,maxPoint.y,minPoint.z);
  points[7] = maxPoint;
  
  return points;
}

}

