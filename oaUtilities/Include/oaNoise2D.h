#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaGrid2D.h"

namespace oaEngineSDK{

/**
 * @brief interface for the noises 2d
*/
class OA_UTILITY_EXPORT Noise2D
{

 public:
  /**
   * @brief the value of the perlin noise at a certain point
   * @param point 
   * @return 
  */
  virtual float 
  valueAt(const Vector2f& point) = 0;

  /**
   * @brief fills a grid with the values of the noise
   * @param grid 
   * @param scale how separated the gradients are going to be from each other
  */
  void
  fillGrid(Grid2D<float>& grid,float scale);
};

}


