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
class Model
{
 private:
  
  /**
   * @brief the textures of the model
  */
  Vector<Texture> textures;

  /**
   * @brief the meshes of the model
  */
  Vector<Mesh> meshes;
};

}

