/**
 * @file oaSphere.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {

/**
 * @brief class for a mathematical shpere
*/
class OA_UTILITY_EXPORT Sphere
{
 public:
  /**
   * @brief default constructor for the Sphere
  */
  Sphere() = default;

  /**
   * @brief parametrized construcrtor for the Sphere
   * @param _center 
   * @param _radius 
  */
  Sphere(const Vector3f& center, float radius) : m_center(center), m_radius(radius) {}

  ~Sphere() = default;

  /**
   * @brief getter for the center
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getCenter() const {
    return m_center;
  }

  /**
  * @brief getter for the radius
  * @return 
  */
  FORCEINLINE float const 
  getRadius() const {
    return m_radius;
  }

  /**
   * @brief setter for the center
   * @param _center 
  */
  FORCEINLINE void 
  setCenter(const Vector3f& center) {
    m_center = center;
  }

  /**
   * @brief setter for the radius
   * @param _radius 
  */
  FORCEINLINE void 
  setRadius(float radius) {
    m_radius = radius;
  }

 private:
  /**
   * @brief the point where the center of the sphere is
  */
  Vector3f m_center;
  /**
   * @brief the radius of the sphere
  */
  float m_radius;
};

}
