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
  Sphere(const Vector3f& _center, float _radius) :center(_center), radius(_radius) {}

  ~Sphere() = default;

  /**
   * @brief getter for the center
   * @return 
  */
  FORCEINLINE const Vector3f& 
  getCenter() const {
    return center;
  }

  /**
  * @brief getter for the radius
  * @return 
  */
  FORCEINLINE float const 
  getRadius() const {
    return radius;
  }

  /**
   * @brief setter for the center
   * @param _center 
  */
  FORCEINLINE void 
  setCenter(const Vector3f& _center) {
    center = _center;
  }

  /**
   * @brief setter for the radius
   * @param _radius 
  */
  FORCEINLINE void 
  setRadius(float _radius) {
    radius = _radius;
  }

  /**
   * @brief checks if the point is inside the sphere
   * @param point 
   * @return 
  
  bool
  isInside(const Vector3f& point);

  /**
   * @brief checks if the line overlap with the sphere
   * @param l 
   * @return 
  
  bool
  overlap(Line& l);

  /**
   * @brief checks if 2 spheres are overlaping
   * @param s 
   * @return 
  
  bool
  overlap(const Sphere& s);*/

 private:
  /**
   * @brief the point where the center of the sphere is
  */
  Vector3f center;
  /**
   * @brief the radius of the sphere
  */
  float radius;

  friend class PlatformMath;
};

}
