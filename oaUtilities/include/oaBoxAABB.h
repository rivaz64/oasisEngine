/**
 * @file oaBoxAABB.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {
/**
 * @brief a bounding box aligned to the axis
*/
class OA_UTILITY_EXPORT BoxAABB
{
 public:
  /**
   * @brief default constructor for the AABB box
  */
  BoxAABB()=default;

  /**
   * @brief constuctor for a box from 2 points
   * @param A
   * @param B 
  */
  BoxAABB(const Vector3f& A, const Vector3f& B);

  ~BoxAABB() = default;

  /**
   * @brief if a point is inside the box
   * @param point 
   * @return 
  */
  bool 
  isPointInside(const Vector3f& point);

  /**
   * @brief if the 2 boxes are overlapping
   * @param box 
   * @return 
  */
  bool
  overlap(const BoxAABB& box);

  /**
   * @brief checks if the sphere and this box collides
   * @param s 
   * @return 
  */
  bool 
  overlap(const Sphere& s);

private:

  /**
   * @brief the minimum values of the box in each axis
  */
  Vector3f minPoint;
  /**
   * @brief the maximum values of the box in each axis
  */
  Vector3f maxPoint;

  friend class PlatformMath;
};

}


