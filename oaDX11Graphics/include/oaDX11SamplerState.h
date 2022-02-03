/**
* @file oaDX11SamplerState.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/9/2021
*/

#pragma once

#include "oaSamplerState.h"
#include <d3d11.h>

namespace oaEngineSDK {

class DX11SamplerState:
  public SamplerState
{
 public:

   //DX11SamplerState(SamplerDesc descriptor);

  ~DX11SamplerState();

  bool
  init(SamplerDesc descriptor) override;

 public:

  ID3D11SamplerState* m_samplerState;
};

}


