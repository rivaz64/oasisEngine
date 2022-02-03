/**
* @file oaDepthStencil.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/1/2021
*/

#pragma once

#include "oaDepthStencil.h"

namespace oaEngineSDK{

class OGL_DepthStencil :
    public DepthStencil
{
 public:

  bool
  init(DepthStencilDesc descritor, SPtr<Texture> texture) override;
};

}


