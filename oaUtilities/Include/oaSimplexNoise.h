/**
 * @file oaSimplexNoise.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 1/10/2021
 */

#pragma once

#include "oaVector2f.h"
#include "oaGrid2D.h"
#include "oaNoise2D.h"


namespace oaEngineSDK{

/**
 * @brief perlin noise 2D generation
*/
class OA_UTILITY_EXPORT SimplexNoise :
  public Noise2D
{
 public:
  /**
   * @brief he value of the simplex noise at a certain point
   * @param point 
   * @return 
  */
  float 
  valueAt(const Vector2f& point) override;

 private:
  static float
  calculateGradient(const Vector2f& gradient, const Vector2f& offset);
};

}


