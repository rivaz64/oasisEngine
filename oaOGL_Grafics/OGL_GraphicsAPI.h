/**
* @file oaOGL_GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesOGL.h"
#include "oaGraphicAPI.h"

namespace oaEngineSDK{

class OA_OGL_EXPORT OGL_GraphicsAPI :
  public GraphicAPI
{
public:
  void
  initialize() override;

protected:

  OGL_GraphicsAPI() = default;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


