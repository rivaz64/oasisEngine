/**
* @file oaRect.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once
#include"oaPrerequisitesUtilities.h"
#include "oaVector2f.h"

namespace oaEngineSDK{
/**
 * @brief a bounding box aligned to the axis in 2d
*/
class OA_UTILITY_EXPORT Rect
{
public:

  /**
  * @brief default constructor for the rect
  */
  Rect()=default;

  /**
  * @brief constuctor for a box from 2 points
  * @param A
  * @param B 
  */
  Rect(const Vector2f& A, const Vector2f& B);

  ~Rect() = default;

  /**
  * @brief if a point is inside the box
  * @param point 
  * @return 
  */
  bool 
  isPointInside(const Vector2f& point);

private:

  /**
  * @brief the minimum values of the box in each axis
  */
  Vector2f minPoint;
  /**
  * @brief the maximum values of the box in each axis
  */
  Vector2f maxPoint;
};

}


