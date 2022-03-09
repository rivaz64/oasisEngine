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

  points[0] = m_minPoint;
  points[1] = Vector3f(m_maxPoint.x,m_minPoint.y,m_minPoint.z);
  points[2] = Vector3f(m_minPoint.x,m_maxPoint.y,m_minPoint.z);
  points[3] = Vector3f(m_minPoint.x,m_minPoint.y,m_maxPoint.z);
  points[4] = Vector3f(m_minPoint.x,m_maxPoint.y,m_maxPoint.z);
  points[5] = Vector3f(m_maxPoint.x,m_minPoint.y,m_maxPoint.z);
  points[6] = Vector3f(m_maxPoint.x,m_maxPoint.y,m_minPoint.z);
  points[7] = m_maxPoint;
  
  return points;
}

}

