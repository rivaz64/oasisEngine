/**
* @file oaDX11RenderTarget.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include <oaRenderTarget.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11RenderTarget :
  public RenderTarget
{
 public:

  ~DX11RenderTarget();

  bool 
  init(SPtr<Texture> texture) override;

  void
  release();

 private:

  ID3D11RenderTargetView* m_renderTargetView = nullptr;

  friend class DX11GraphicAPI;
};

}



