/**
* @file oaDX11PixelShader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include "oaDX11Shader.h"
#include <d3d11.h>

namespace oaEngineSDK{

class DX11PixelShader :
  public DX11Shader
{
 public:

  ~DX11PixelShader();

  bool 
  compileFromFile(String file);

  void
  set() override;

 private:
  ID3D11PixelShader* shader = nullptr;

};

}


