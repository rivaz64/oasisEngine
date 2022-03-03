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
class OA_UTILITY_EXPORT AABB
{
 public:
  /**
   * @brief default constructor for the AABB box
  */
  AABB()=default;

  /**
   * @brief constuctor for a box from 2 points
   * @param A
   * @param B 
  */
  /*AABB(const Vector3f& A, const Vector3f& B) :
    minPoint(Math::min(A.x,B.x),Math::min(A.y,B.y) ,Math::min(A.z,B.z)),
    maxPoint(Math::max(A.x,B.x),Math::max(A.y,B.y) ,Math::max(A.z,B.z)) {}*/

  ~AABB() = default;

  /**
   * @brief getter for the min point
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getMinPoint() const {
    return minPoint;
  }

  /**
   * @brief getter for the max point
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getMaxPoint() const {
    return maxPoint;
  }

  FORCEINLINE void
  setMinPoint(const Vector3f& _minPoint) {
    minPoint = _minPoint;
  }

  FORCEINLINE void
  setMaxPoint(const Vector3f& _maxPoint) {
    maxPoint = _maxPoint;
  }

  Vector<Vector3f>
  getPoints() const;

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


