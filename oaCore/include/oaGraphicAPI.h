/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>
#include <oaColor.h>


namespace oaEngineSDK{

namespace GRAPHIC_API {
enum E{
  NONE=0,
  DIRECTX11,
  OPENGL
};
};

/**
 * @brief everything used for graphycs
*/
class OA_CORE_EXPORT GraphicAPI :
  public Module<GraphicAPI>
{
 protected:

  GraphicAPI() = default;

  ~GraphicAPI() = default;

 public:

  /**
   * @brief initializes everything needed for the graphics
   * @return if the initialization was correct
  */
  virtual bool
  initialize();

  virtual void 
  createWindow(void* /*app*/, const Vector2U& /*size*/, const String& /*name*/){}

  /**
   * @brief if the grafics are still doing things
   * @return if it should continue running
  */
  virtual bool
  isRunning();

  /**
   * @brief manages the the events that the graphics api detects
  */
  virtual void
  events() {}

  /**
   * @brief creates a shader program
   * @return 
  */
  virtual SPtr<ShaderProgram> 
  createShaderProgram();

  /**
   * @brief creates a vertex shader
   * @return 
  */
  virtual SPtr<Shader>
  createVertexShader(); 

  /**
   * @brief creates a pixel shader
   * @return 
  */
  virtual SPtr<Shader>
  createPixelShader(); 

  /**
   * @brief creates a buffer
   * @return 
  */
  virtual SPtr<Buffer> 
  createBuffer();

  /**
   * @brief creates a vertexBuffer
   * @return 
  */
  virtual SPtr<VertexBuffer> 
  createVertexBuffer();

  /**
   * @brief creates a IndexBuffer
   * @return 
  */
  virtual SPtr<IndexBuffer> 
  createIndexBuffer();

  /**
  * @brief creates a texture
  * @return 
  */
  virtual SPtr<Texture> 
  createTexture();

  /**
   * @brief creates a sampler state
   * @param the atributes of the sampler state
   * @return 
  */
  virtual SPtr<SamplerState>
  createSamplerState(const SamplerDesc& /*descriptor*/);

  /**
   * @brief creates a render target
   * @param texture the texture for the render target
   * @return 
  */
  virtual SPtr<RenderTarget>
  createRenderTarget(SPtr<Texture> /*texture*/);

  /**
   * @brief creates a depth stencil
   * @param description 
   * @param texture 
   * @return 
  */
  virtual SPtr<DepthStencil>
  createDepthStencil(const DepthStencilDesc& /*description*/, SPtr<Texture> /*texture*/);

  /**
   * @brief creates a new rasterizer
   * @return 
  */
  virtual SPtr<Rasterizer>
  createRasterizer();

   /**
   * @brief creates a new blender
   * @return 
  */
  virtual SPtr<Blender>
  createBlender();

  /**
  * @brief sets the color of the background
  * @param color 
  */
  virtual void
  setBackgroundColor(const Color& /*color*/) {}

  virtual SPtr<Texture>
  getBackBuffer();

  /**
   * @brief draws to the back buffer
   * @param indexes 
  */
  virtual void
  draw(uint32 /*indexes*/) {}

  /**
   * @brief shows the things that where rendered
   * @param indexes number of indexes to draw
  */
  virtual void
  show() {}

  /**
  * @brief sets the vertex bubbers that are going to be drawn
  * @param buffer 
  */
  virtual void
  setIndexBuffer(const SPtr<Buffer>& /*buffer*/){}

  /**
   * @brief set the texture the shader is going to use
   * @param texture 
   * @param location 
  */
  virtual void
  setTexture(const SPtr<Texture> /*texture*/,uint8 /*location*/){}

  /**
   * @brief sets a constant buffer to be used in a vertex shader
   * @param buffer 
   * @param location the location in th shader
  */
  virtual void
  setVSBuffer(const SPtr<Buffer> /*buffer*/,uint32 /*location*/){}

  /**
   * @brief sets a constant buffer to be used in a pixel shader
   * @param buffer 
   * @param location the location in th shader
  */
  virtual void
  setPSBuffer(const SPtr<Buffer> /*buffer*/,uint32 /*location*/){}

  /**
   * @brief sets a sampler tate
   * @param  
  */
  virtual void
  setSamplerState(const SPtr<SamplerState> /*sampler*/) {}

  /**
   * @brief sets a rasterizer to be used
   * @param  
  */
  virtual void
  setRasterizer(const SPtr<Rasterizer> /*rasterizer*/) {}

  /**
   * @brief sets a blender to be used
   * @param  
  */
  virtual void
  setBlender(const SPtr<Blender> /*blender*/) {}

  /**
   * @brief clears a render target
   * @param renderTarget 
  */
  virtual void
  clearRenderTarget(SPtr<RenderTarget> renderTarget){}

  /**
   * @brief clears a depth stencil to 1s
   * @param depthStencil 
  */
  virtual void 
  clearDepthStencil(SPtr<DepthStencil> depthStencil) {}

  /**
   * @brief sets the render target to be used
   * @param renderTarget 
  */
  virtual void
  setRenderTarget(const SPtr<RenderTarget> /*renderTarget*/) {}

  /**
   * @brief sets a render target and a depth stencil
   * @param renderTarget 
   * @param depthStencil 
  */
  virtual void
  setRenderTargetAndDepthStencil(
    const SPtr<RenderTarget> /*renderTarget*/,
    const SPtr<DepthStencil> /*depthStencil*/
  ) {}

  /**
   * @brief sets the render target and the depth stencil to null
  */
  virtual void
  unsetRenderTargetAndDepthStencil() {}

  /**
   * @brief initializes everything needed for the window
   * @param window 
  */
  virtual void
  initWindow(void* /*window*/) {}

  /**
   * @brief sets the window to be used
   * @param  
  */
  virtual void
  setWindow() {}

  virtual void*
  getWindow() { return nullptr;}

  virtual void*
  getDevice() {return nullptr;}

  virtual void*
  getContext() {return nullptr;}

 public:

  /**
   * @brief the width of the window at the begining
  */
  uint32 m_windowWidth = 800;

  /**
  * @brief the height of the window at the begining
  */
  uint32 m_windowHeight = 600;

  /**
   * @brief the function for procecing the events
  */
  void* eventsFunction = nullptr;

  /**
  * @brief the graphical API that has been loaded
  */
  GRAPHIC_API::E m_actualGraphicAPI = GRAPHIC_API::NONE;

 protected:

  friend class Module<GraphicAPI>;
};


}


