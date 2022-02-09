/**
* @file oaDX11ShaderProgram.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include <oaShaderProgram.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11ShaderProgram :
  public ShaderProgram
{
 public:

  void
  set() override;

};

}


