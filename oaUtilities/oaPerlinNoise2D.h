/**
 * @file oaPerlinNoise2D.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 11/22/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector2f.h"
#include "oaGrid2D.h"

namespace oaEngineSDK{

class PerlinNoise2D
{
  /**
   * @brief the value of the perlin noise at a certain point
   * @param point 
   * @return 
  */
  float 
  valueAt(const Vector2f& point);

  /**
   * @brief fills a grid with the values of the noise
   * @param grid 
   * @param scale how separated the gradients are going to be from each other
  */
  void
  fillGrid(Grid2D<float>& grid,float scale);
};

}


