/**
* @file oaDX11Texture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once
#include <oaTexture.h>
#include <oaPath.h>
#include <d3d11.h>
#include <d3dx11.h>


namespace oaEngineSDK{

class DX11Texture:
  public Texture
{

 public:

  ~DX11Texture();

  void
  release() override;

  void*
  getId() override;

  void
  initFromImage(SPtr<Image> image) override;

  void
  initForDepthStencil(const Vector2U& size) override;

 private:

  ID3D11ShaderResourceView* m_shaderResourceView;

  ID3D11Texture2D* m_texture;

  friend class DX11GraphicAPI;
  friend class DX11DepthStencil;
  friend class DX11RenderTarget;
};

}


