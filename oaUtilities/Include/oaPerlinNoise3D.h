/**
 * @file oaPerlinNoise3D.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 12/17/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaGrid3D.h"

namespace oaEngineSDK{

/**
 * @brief a noise generator in 3 dimencions
*/
class OA_UTILITY_EXPORT PerlinNoise3D
{
 public:
  /**
   * @brief the value of the perlin noise at a certain point
   * @param point 
   * @return 
  */
  static float 
  valueAt(const Vector3f& point);

  /**
   * @brief fills a grid with the values of the noise
   * @param grid 
   * @param scale how separated the gradients are going to be from each other
  */
  static void
  fillGrid(Grid3D<float>& grid,float scale);
};

}


