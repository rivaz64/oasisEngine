/**
 * @file oaRandom.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"
#include "oaVector2f.h"

namespace oaEngineSDK {

class Random
{
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
  noise2D(const Vector2f& point);

  /**
   * @brief generaates a random 2d vector
   * @return 
  */
  static Vector2f
  vector();

  /**
   * @brief generaates a random 2d vector at a certain point
   * @return 
  */
  static Vector2f
  vector(const Vector2f& point);
};

}


