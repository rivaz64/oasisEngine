/**
* @file oaDX11Texture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once
#include "oaTexture.h"
#include <d3d11.h>
#include <d3dx11.h>
#include "oaPath.h"

namespace oaEngineSDK{



class DX11Texture:
  public Texture
{

 public:

  ~DX11Texture();

  bool
  loadFromFile(const Path& file) override;

  bool
  init(TextureDesc description);

  bool
  init(TextureDesc description,ShaderResourseViewDesc descriptionSRV);

  void*
  getId() override;


 private:

  ID3D11ShaderResourceView* shaderResourceView;

  ID3D11Texture2D* texture;

  friend class DX11GraphicAPI;
  friend class DX11DepthStencil;
  friend class DX11RenderTarget;
};

}


