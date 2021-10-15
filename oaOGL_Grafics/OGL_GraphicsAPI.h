/**
* @file oaOGL_GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesOGL.h"
#include "oaGraphicAPI.h"
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

class OA_OGL_EXPORT OGL_GraphicsAPI :
  public GraphicAPI
{
public:

  bool
  initialize() override;

  bool
  isRunning() override;

  void
  events() override;


protected:

  OGL_GraphicsAPI() = default;

  ~OGL_GraphicsAPI();

  GLFWwindow* window;

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}


