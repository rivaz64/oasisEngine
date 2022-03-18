/**
* @file oaDX11DepthStencil.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/11/2021
*/

#pragma once
#include <oaDepthStencil.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11DepthStencil :
  public DepthStencil
{
 public:

  ~DX11DepthStencil();

  bool
  init(SPtr<Texture> texture) override;

  void
  release();

  ID3D11DepthStencilView* m_depthStencilView = nullptr;

  ID3D11DepthStencilState* m_depthStencilState = nullptr;
};

}


