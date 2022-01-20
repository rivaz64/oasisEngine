/**
* @file oaMaterial.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief a class for materials
*/
class OA_CORE_EXPORT Material
{
 public:

  /**
   * @brief sets this material to be used in the shader
  */
  void
  set();
  
  /**
   * @brief the textures of this material
  */
  Vector<SPtr<Texture>> textures;

  /**
   * @brief the vertex shader of this material
  */
  SPtr<Shader> vertexShader;

  /**
   * @brief the pixel shader of this material
  */
   SPtr<Shader> pixelShader;

   String name;
};

}


