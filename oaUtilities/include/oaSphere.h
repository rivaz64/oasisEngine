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
class Sphere
{
 public:
  Sphere() = default;
  Sphere(const Vector3f& _center, float _radius) :center(_center), radius(_radius) {}
  ~Sphere() = default;

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


