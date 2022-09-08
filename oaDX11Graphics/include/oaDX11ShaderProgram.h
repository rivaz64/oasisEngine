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
  attach(WPtr<Shader> shader) override;

  void
  set() override;

 protected:
  /**
   * @brief the shaders used by this program
  */
  Vector<WPtr<Shader>> m_shaders;
};

}


