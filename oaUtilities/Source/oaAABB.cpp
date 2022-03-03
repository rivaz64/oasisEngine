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
  return {minPoint,
          {maxPoint.x,minPoint.y,minPoint.z},
          {minPoint.x,maxPoint.y,minPoint.z},
          {minPoint.x,minPoint.y,maxPoint.z},
          {minPoint.x,maxPoint.y,maxPoint.z},
          {maxPoint.x,minPoint.y,maxPoint.z},
          {maxPoint.x,maxPoint.y,minPoint.z},
          maxPoint};
}

}

