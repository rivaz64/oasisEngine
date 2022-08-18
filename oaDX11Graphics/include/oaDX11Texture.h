/**
* @file oaDX11Texture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include <oaTexture.h>
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

  bool
  init(const Vector2I& size,BIND::E bind, FORMAT::E format, const void* data = nullptr, uint32 pitch = 0) override;

  bool
  createShaderResource(FORMAT::E format) override;

  bool
  createRenderTarget(FORMAT::E format) override;

  bool
  createDepthStencil(FORMAT::E format) override;

 public:

  ID3D11Texture2D* m_texture = nullptr;

  ID3D11ShaderResourceView* m_shaderResourceView = nullptr;

  ID3D11RenderTargetView* m_renderTargetView = nullptr;

  ID3D11DepthStencilView* m_depthStencilView = nullptr;

  friend class DX11GraphicAPI;
};

}


