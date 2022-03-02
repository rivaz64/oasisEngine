/**
* @file oaRasterizer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
*/

#pragma once

#include <oaRasterizer.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11Rasterizer:
  public Rasterizer
{
 public:

  bool 
  init(CULLING::E culling, FILL_MODE::E fillMode) override;

  ID3D11RasterizerState* m_id;
};

}


