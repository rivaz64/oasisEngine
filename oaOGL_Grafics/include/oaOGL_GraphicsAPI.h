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
    setBackgroundColor(const Vector4f& color) override;

  void
  createShaderProgram() override;

  void
  clear() override;

  void
  draw(uint32 indexes) override;

  void
  show() override;

  SPtr<Buffer>
  createBuffer() override;

  SPtr<Texture> 
  createTexture() override;

  void
  setVertexBuffer(const SPtr<Buffer>& buffer) override;

  void
  setIndexBuffer(const SPtr<Buffer>& buffer) override;

  void
  setTexture(const SPtr<Texture>& texture) override;

  void
  setBuffer(const SPtr<Buffer>& buffer,uint32 location) override;

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


