/**
* @file oaTriangle.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/18/2022
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK{

/**
 * @brief a geometrical triangle to be divided
*/
class OA_UTILITY_EXPORT Triangle
{
 public:
  Triangle() = default;

  Triangle(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3) :
    m_point1(point1), m_point2(point2), m_point3(point3) {}

  /**
   * @brief separates the triangle cutting it by the given plane
   * @param plane 
  */
  bool
  separate(const Plane& plane,
           Vector<Vector3f>& points, 
           Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide,
           bool& isTriFront);

  
 private:

  Vector3f m_point1;
  Vector3f m_point2;
  Vector3f m_point3;

};


}

