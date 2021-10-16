/**
* @file oaOGL_PixelShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include"oaOGL_Shader.h"

namespace oaEngineSDK{

class OGL_PixelShader :
  public OGL_Shader
{
 public:

  bool 
  compileFromFile(String file);
};

}

