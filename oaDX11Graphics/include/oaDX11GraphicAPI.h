/**
* @file DX11GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesDX11.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

class OA_DX11_EXPORT DX11GraphicAPI :
  public GraphicAPI
{
 public:
  void
  initialize() override;

 protected:

  DX11GraphicAPI() = default;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


