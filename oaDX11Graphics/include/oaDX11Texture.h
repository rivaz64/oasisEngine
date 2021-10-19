/**
* @file oaDX11Texture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once
#include "oaTexture.h"
#include <d3d11.h>
#include <d3dx11.h>

namespace oaEngineSDK{

class DX11Texture:
  public Texture
{

 public:

  bool
  loadFromFile(const String& file);

 private:

  ID3D11ShaderResourceView* texture;
};

}


