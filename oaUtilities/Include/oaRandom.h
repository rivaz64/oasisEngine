/**
 * @file oaRandom.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK {

class OA_UTILITY_EXPORT Random
{
 public:
  /**
   * @brief a random number between 0 and 1
   * @return 
  */
  static FORCEINLINE float
  unit() {
    return static_cast<float>(std::rand()) / RAND_MAX;
  }

  /**
   * @brief a random number between 0 and 1
   * @return
  */
  static FORCEINLINE float
  symmetric() {
    return (static_cast<float>(std::rand())  / RAND_MAX)*2.f-1.f;
  }

  /**
   * @brief the value of a 2d noise at a certain point
   * @param point 
   * @return 
  */
  static float 
  noise1D(const float point);

  /**
   * @brief the value of a 2d noise at a certain point
   * @param point 
   * @return 
  */
  static float 
  noise2D(const Vector2f& point);

  /**
   * @brief the value of a 3d noise at a certain point
   * @param point 
   * @return 
  */
  static float 
  noise3D(const Vector3f& point);

  /**
   * @brief generaates a random 2d vector
   * @return 
  */
  static Vector2f
  vector2();

  /**
   * @brief generaates a random 2d vector at a certain point
   * @return 
  */
  static Vector2f
  vector2(const Vector2f& point);

  /**
   * @brief generates a random number with a gaussian distribution 
   * @return 
  */
  static float
  gaussian();

  /**
   * @brief generates a random number with a gaussian distribution 
   * @return 
  */
  static float
  gaussian(const float point);


  /**
   * @brief generaates a random 3d vector
   * @return 
  */
  static Vector3f
  vector3();

  /**
   * @brief generaates a random 3d vector
   * @return 
  */
  static Vector3f
  vector3(const Vector3f& point);
};

}


