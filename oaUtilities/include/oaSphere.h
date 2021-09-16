/**
 * @file oaSphere.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/15/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief class for a mathematical shpere
*/
class OA_UTILITY_EXPORT Sphere
{
 public:
  Sphere() = default;
  Sphere(const Vector3f& _center, float _radius) :center(_center), radius(_radius) {}
  ~Sphere() = default;

  /**
   * @brief getter for the center
   * @return 
  */
  FORCEINLINE const Vector3f& const getCenter() const {
    return center;
  }

  FORCEINLINE const float& const getRadius() const {
    return radius;
  }

  /**
   * @brief checks if the point is inside the sphere
   * @param point 
   * @return 
  */
  bool
    isInside(const Vector3f& point);

  /**
   * @brief checks if the line collides with the sphere
   * @param l 
   * @return 
  */
  bool
    collides(Line& l);

  /**
   * @brief checks if 2 spheres are colliding
   * @param s 
   * @return 
  */
  bool
    collides(const Sphere& s);

 private:
   /**
    * @brief the point where the center of the sphere is
   */
   Vector3f center;
   /**
    * @brief the radius of the sphere
   */
   float radius;
};

}


