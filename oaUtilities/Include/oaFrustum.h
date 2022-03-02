/**
* @file oaFrustrum.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/9/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaPlane.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Frustum
{
 public:
  /**
   * @brief 
  */
  void
  calculatePlanes(const Vector3f& location,
                  const Matrix3f& axis,
                  const float nearPlaneDistance,
                  const float farPlaneDistance,
                  const float viewAngle,
                  const float ratio);

  static Vector<Vector3f>
  calculatePoints(const Vector3f& location,
                  const Matrix3f& axis,
                  const float nearPlaneDistance,
                  const float farPlaneDistance,
                  const float viewAngle,
                  const float ratio);

 private:
  /**
   * @brief the near plane of the frustrum
  */
  Plane m_nearPlane;

  /**
   * @brief the far plane of the frustrum
  */
  Plane m_farPlane;

  /**
   * @brief the top plane of the frustrum
  */
  Plane m_topPlane;

  /**
   * @brief the bottom plane of the frustrum
  */
  Plane m_bottomPlane;

  /**
   * @brief the near left of the frustrum
  */
  Plane m_leftPlane;

  /**
   * @brief the right plane of the frustrum
  */
  Plane m_rightPlane;
};

}


