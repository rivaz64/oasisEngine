/**
* @file oaOGL_GraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include <oaGraphicAPI.h>
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

class OGL_GraphicsAPI :
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
  setBackgroundColor(const Color& color) override;

  SPtr<ShaderProgram>
  createShaderProgram() override;

  void
  draw(uint32 indexes) override;

  void
  show() override;

  SPtr<Buffer>
  createBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  void
  setIndexBuffer(const SPtr<Buffer>& buffer) override;

  void*
  getWindow() override;

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


