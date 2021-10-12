/**
* @file oaModel.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaMesh.h"
#include "oaTexture.h"


namespace oaEngineSDK{

/**
 * @brief class for 3D models
*/
class OA_UTILITY_EXPORT Model
{
 public:

  /**
   * @brief default constructor for the model
  */
  Model() = default;

  ~Model() = default;

 protected:
  
  /**
   * @brief the textures of the model
  */
  Vector<SPtr<Texture>> textures;

  /**
   * @brief the meshes of the model
  */
  Vector<SPtr<Mesh>> meshes;
};

}

