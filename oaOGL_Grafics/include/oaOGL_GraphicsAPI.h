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

  void
  setBackgroundColor(const Vector4f& color) override;

  void
  show() override;

  SPtr<Buffer>
  createBuffer() override;

protected:

  OGL_GraphicsAPI() = default;

  ~OGL_GraphicsAPI();

 public:

  unsigned int shaderProgram;

 protected:

  GLFWwindow* window = nullptr;

  

  friend class GraphicAPI;
  friend class Module<GraphicAPI>;
};

}

