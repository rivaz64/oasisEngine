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

namespace oaEngineSDK{

/**
 * @brief a noise generator in 2 dimencions
*/
class OA_UTILITY_EXPORT PerlinNoise2D
{
 public:
  /**
   * @brief the value of the perlin noise at a certain point
   * @param point 
   * @return 
  */
  static float 
  valueAt(const Vector2f& point);

  /**
   * @brief fills a grid with the values of the noise
   * @param grid 
   * @param scale how separated the gradients are going to be from each other
  */
  static void
  fillGrid(Grid2D<float>& grid,float scale);

  /**
   * @brief fills a grid taking the z axis as the attitude to fill
   * @param grid 
   * @param scale  how separated the gradients are going to be from each other
   * @param bias the result of the perlin plus this
   * @param amplitud the result of the perlin times this
  */
  static void
  fillGrid(Grid3D<bool>& grid,float scale,float bias, float amplitud);
};

}


