/**
 * @file oaBoxAABB.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {

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
   * @brief setter for the minimum points
   * @param _minPoint 
  */
  FORCEINLINE void 
  setMinPoint(const Vector3f& _minPoint) {
    minPoint = _minPoint;
  }

  /**
   * @brief setter for the maximum points
   * @param _maxPoint
  */
  FORCEINLINE void 
  setMaxPoint(const Vector3f& _maxPoint) {
    maxPoint = _maxPoint;
  }

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
  bool overlap(const Sphere& s);

private:

  /**
   * @brief the minimum values of the box in each axis
  */
  Vector3f minPoint;
  /**
   * @brief the maximum values of the box in each axis
  */
  Vector3f maxPoint;
};

}


