/**
* @file oaOGL_ShaderProgram.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/9/2022
*/

#pragma once

#include <oaShaderProgram.h>

namespace oaEngineSDK{

class OGL_ShaderProgram :
  public ShaderProgram
{
 public:

  OGL_ShaderProgram();

  void 
  attach(SPtr<Shader> shader) override;

  void
  set() override;

  uint32 id;
};


}

