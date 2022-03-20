/**
* @file oaRasterizer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
*/

#pragma once

#include <oaRasterizerState.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11RasterizerState:
  public RasterizerState
{
 public:

  ~DX11RasterizerState();

  bool 
  init(CULLING::E culling, FILL_MODE::E fillMode) override;

  void
  release();

 private:

  ID3D11RasterizerState* m_id = nullptr;

  friend class DX11GraphicAPI;
};

}


