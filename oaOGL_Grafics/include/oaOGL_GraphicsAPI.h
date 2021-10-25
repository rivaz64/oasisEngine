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

  void
  onShutDown() override;

  bool
  initialize() override;

  bool
  isRunning() override;

  void
  events() override;

  void
  setBackgroundColor(const Vector4f& color) override;

  void
  clear() override;

  void
  show() override;

  void
  initImGui() override;

  void
  newImGuiFrame() override;

  SPtr<Buffer>
  createBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  void
  setVertexBuffer(const SPtr<Buffer>& buffer) override;

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


