/**
* @file oaCapsule.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Capsule
{
 public:
  /**
  * @brief default constructor for the Sphere
  */
  Capsule() = default;

  /**
  * @brief parametrized construcrtor for the Capsule
  * @param _center 
  * @param _radius 
  */
  Capsule(const Vector3f& base, float radius,float height) : 
    m_base(base), m_radius(radius),m_height(height) {}

  ~Capsule() = default;

  /**
   * @brief getter for the base point
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getBase() const {
    return m_base;
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
  * @brief getter for the height
  * @return 
  */
  FORCEINLINE float const 
  getHeight() const {
    return m_height;
  }

  /**
  * @brief setter for the base
  * @param _center 
  */
  FORCEINLINE void 
  setBase(const Vector3f& base) {
    m_base = base;
  }

  /**
  * @brief setter for the radius
  * @param _radius 
  */
  FORCEINLINE void 
  setRadius(float radius) {
    m_radius = radius;
  }

  /**
  * @brief setter for the height
  * @param _radius 
  */
  FORCEINLINE void 
  setHeight(float height) {
    m_height = height;
  }
 private:

  /**
  * @brief the lowest point of the capsule
  */
  Vector3f m_base;

  /**
  * @brief the radius of the capsule
  */
  float m_radius;

  /**
  * @brief the height of the capsule
  */
  float m_height;

  friend class PlatformMath;
};

}

