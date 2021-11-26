/**
* @file oaMaterial.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once
#include "oaPrerequisitesCore.h"
#include "oaTexture.h"
#include "oaShader.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Material
{
 public:

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
   * @brief the pixel shader of this shader
  */
  SPtr<Shader> pixelShader;
};

}


