/**
* @file oaDX11Blender.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/26/2022
*/

#pragma once

#include <oaBlender.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11Blender :
  public Blender
{
 public:

  bool 
  init() override;

  ID3D11BlendState* m_id;
};

}


