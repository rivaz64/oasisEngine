/**
* @file Grid2D.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/21/2021
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector2U.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Grid2D
{
 public:
  
  /**
   * @brief initializes a grid of a certain size
   * @param size 
  */
  Grid2D(const Vector2U& size);

 private:
  /**
   * @brief all the data of the grid
  */
  int32* data;
};

}


