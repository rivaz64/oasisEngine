/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

class DX11GraphicAPI;

class OA_CORE_EXPORT GraphicAPI :
  public Module<GraphicAPI>
{
public:

  virtual void
  initialize();


 protected:

  GraphicAPI() = default;

  friend class Module<GraphicAPI>;
};


}


