/**
 * @file oaPerlinNoise2D.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 11/22/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector2f.h"
#include "oaGrid2D.h"
#include "oaGrid3D.h"
#include "oaNoise2D.h"

namespace oaEngineSDK{

/**
 * @brief a noise generator in 2 dimencions
*/
class OA_UTILITY_EXPORT PerlinNoise2D :
  public Noise2D
{

 public:

  /**
   * @brief the value of the perlin noise at a certain point
   * @param point 
   * @return 
  */
  float 
  valueAt(const Vector2f& point) override;


};

}


