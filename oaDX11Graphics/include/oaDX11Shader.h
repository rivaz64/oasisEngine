/**
* @file oaDX11Shader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaShader.h"


namespace oaEngineSDK{

class OA_DX11_EXPORT DX11Shader :
  public Shader
{
 public:
  bool 
  compileFromFile(String file);
};

}


