/**
* @file oaMesh.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a class for a mesh
*/
class OA_UTILITY_EXPORT Mesh
{
 private:

  /**
   * @brief the indices of the vertices of each triangle
  */
  SPtr<uint32> index;

  /**
   * @brief the location of the vertices of the mesh
  */
  SPtr<float> vertices;

  /**
   * @brief the 
  */
  //SPtr<float> textureCoords;
};

}


