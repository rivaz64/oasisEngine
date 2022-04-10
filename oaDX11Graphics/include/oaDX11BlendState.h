/**
* @file oaDX11Blender.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/26/2022
*/

#pragma once

#include <oaBlendState.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11BlendState :
  public BlendState
{
 public:

  ~DX11BlendState();

  bool 
  init(bool adds) override;

  void
  release();

 private:

  ID3D11BlendState* m_id;

  friend class DX11GraphicAPI;
};

}


