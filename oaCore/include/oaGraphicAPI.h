/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaBuffer.h"
#include "oaTexture.h"
#include "oaSamplerState.h"
#include "oaVector4f.h"
#include "oaSamplerState.h"
#include "oaRenderTarget.h"
#include "oaDepthStencil.h"
#include "oaVector2I.h"
#include "oaShader.h"
#include "oaVertexBuffer.h"
#include "oaIndexBuffer.h"
#include <Windows.h>


namespace oaEngineSDK{

enum class GRAPHIC_API {
  NONE=0,
  DIRECTX11,
  OPENGL
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

  virtual void 
  createShaderProgram() {}

  /**
   * @brief creates a vertex shader
   * @return 
  */
  virtual SPtr<Shader>
  createVertexShader() {return newSPtr<Shader>();}

  /**
   * @brief creates a pixel shader
   * @return 
  */
  virtual SPtr<Shader>
  createPixelShader() {return newSPtr<Shader>();}

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
  createVertexBuffer() {return newSPtr<VertexBuffer>();}

  /**
   * @brief creates a IndexBuffer
   * @return 
  */
  virtual SPtr<IndexBuffer> 
  createIndexBuffer() {return newSPtr<IndexBuffer>();}

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
  createSamplerState(SamplerDesc& /*descriptor*/);

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
  createDepthStencil(DepthStencilDesc& /*description*/, SPtr<Texture> /*texture*/);

  /**
  * @brief sets the color of the background
  * @param color 
  */
  virtual void
  setBackgroundColor(const Vector4f& /*color*/) {}

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
  */
  virtual void
  setTexture(const SPtr<Texture>& /*texture*/){}

  /**
   * @brief sets a constant buffer to be used un a shader
   * @param buffer 
   * @param location the location in th shader
  */
  virtual void
  setBuffer(const SPtr<Buffer>& /*buffer*/,uint32 /*location*/){}

  /**
   * @brief sets a sampler tate
   * @param  
  */
  virtual void
  setSamplerState(const SPtr<SamplerState> /*sampler*/) {}

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
  uint32 windowWidth = 800;

  /**
  * @brief the height of the window at the begining
  */
  uint32 windowHeight = 600;

  WNDPROC eventsFunction = 0;

  /**
  * @brief the graphical API that has been loaded
  */
  GRAPHIC_API actualGraphicAPI = GRAPHIC_API::NONE;

 protected:
  /**
   * @brief the name of the window 
  */
  const String windowName = "Oasis Engine";

  friend class Module<GraphicAPI>;
};


}


