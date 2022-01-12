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

  /**
   * @brief normalizes all the values and then redistrubtes them
   * @param grid the data
   * @param power the power to use in the redistribution
   * @param minValue the value to set at 0 for the redistribution, every value below this one becomes 0
  */
  void
  redistribute(Grid2D<float>& grid,float power, float minValue);
};

}


