/**
* @file oaFrustrum.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/9/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaPlane.h"

namespace oaEngineSDK{

/**
 * @brief class for a frustum of 6 planes
*/
class OA_UTILITY_EXPORT Frustum
{
 public:
  
  Frustum(const Vector3f& location,
          const Matrix3f& axis,
          const float nearPlaneDistance,
          const float farPlaneDistance,
          const float viewAngle,
          const float ratio);

  /**
   * @brief calculates the 6 planes of this frustrum
   * @param location 
   * @param axis 
   * @param nearPlaneDistance 
   * @param farPlaneDistance 
   * @param viewAngle 
   * @param ratio 
  */
  void
  calculatePlanes(const Vector3f& location,
                  const Matrix3f& axis,
                  const float nearPlaneDistance,
                  const float farPlaneDistance,
                  const float viewAngle,
                  const float ratio);

  /**
   * @brief calculates the 8 points of the frustrum
   * @param location 
   * @param axis 
   * @param nearPlaneDistance 
   * @param farPlaneDistance 
   * @param viewAngle 
   * @param ratio 
   * @return 
  */
  static Vector<Vector3f>
  calculatePoints(const Vector3f& location,
                  const Matrix3f& axis,
                  const float nearPlaneDistance,
                  const float farPlaneDistance,
                  const float viewAngle,
                  const float ratio);

  /**
   * @brief calculates if a point is inside of the frustrum
   * @param point 
   * @return 
  */
  bool 
  isInside(const Vector3f& point) const;

  /**
   * @brief calculates if a part of a  sphere is inside of the frustrum
   * @param sphere 
   * @return 
  */
  bool 
  isInside(const Sphere& sphere) const;

  /**
   * @brief calculates if a part of a aabb is inside of the frustrum
   * @param sphere 
   * @return 
  */
  bool 
  isInside(const AABB& box, const Matrix4f& transform) const;

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


