/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>
#include <oaColor.h>
#include "oaFlags.h"


namespace oaEngineSDK{

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
  initialize(void* /*window*/);

  virtual void* 
  createWindow(void* ,void* /*app*/, const Vector2U& /*size*/, const String& /*name*/);

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
   * @brief creates a pixel shader
   * @return 
  */
  virtual SPtr<Shader>
  createHullShader(); 

  /**
   * @brief creates a pixel shader
   * @return 
  */
  virtual SPtr<Shader>
  createDomainShader(); 

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
  createSamplerState();

  /**
   * @brief creates a new rasterizer
   * @return 
  */
  virtual SPtr<RasterizerState>
  createRasterizerState();

   /**
   * @brief creates a new blender
   * @return 
  */
  virtual SPtr<BlendState>
  createBlendState();

  /**
  * @brief sets the color of the background
  * @param color 
  */
  virtual void
  setBackgroundColor(const Color& /*color*/) {}

  virtual SPtr<Texture>
  getBackBuffer();

  /**
   * @brief draws without using index for the tris
   * @param the number of vertices
  */
  virtual void
  draw(SIZE_T /*vertices*/) {}

  /**
   * @brief draws using index for the tris
   * @param the number of indexes 
  */
  virtual void
  drawIndex(SIZE_T /*indexes*/) {}

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
  setTexture(const SPtr<Texture> /*texture*/,uint32 /*location*/){}

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
   * @brief sets a constant buffer to be used in a hull shader
   * @param buffer 
   * @param location the location in th shader
  */
  virtual void
  setHSBuffer(const SPtr<Buffer> /*buffer*/,uint32 /*location*/){}

  /**
   * @brief sets a constant buffer to be used in a hull shader
   * @param buffer 
   * @param location the location in th shader
  */
  virtual void
  setDSBuffer(const SPtr<Buffer> /*buffer*/,uint32 /*location*/){}

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
  setRasterizerState(const SPtr<RasterizerState> /*rasterizer*/) {}

  /**
   * @brief sets a blender to be used
   * @param  
  */
  virtual void
  setBlendState(const SPtr<BlendState> /*blender*/) {}

  /**
   * @brief clears a render target
   * @param renderTarget 
  */
  virtual void
  clearRenderTarget(SPtr<Texture> renderTarget){}

  /**
   * @brief clears a depth stencil to 1s
   * @param depthStencil 
  */
  virtual void 
  clearDepthStencil(SPtr<Texture> depthStencil) {}

  /**
   * @brief sets the render target to be used
   * @param renderTarget 
  */
  virtual void
  setRenderTarget(const SPtr<Texture> /*renderTarget*/) {}

  /**
   * @brief sets the renders target to be used
   * @param renderTarget 
  */
  virtual void
  setRenderTargets(const Vector<SPtr<Texture>>& /*renderTargets*/) {}

  /**
   * @brief sets a render target and a depth stencil
   * @param renderTarget 
   * @param depthStencil 
  */
  virtual void
  setRenderTargetAndDepthStencil(
    const SPtr<Texture> /*renderTarget*/,
    const SPtr<Texture> /*depthStencil*/
  ) {}

   /**
   * @brief sets the render targets and a depth stencil
   * @param renderTarget 
   * @param depthStencil 
  */
  virtual void
  setRenderTargetsAndDepthStencil(
    const Vector<SPtr<Texture>>& /*renderTarget*/,
    const SPtr<Texture> /*depthStencil*/
  ) {}

  /**
   * @brief sets the render target and the depth stencil to null
  */
  virtual void
  unsetRenderTargetAndDepthStencil() {}

  /**
   * @brief sets the render target and the depth stencil to null
  */
  virtual void
  unsetTextures(uint32 /*n*/) {}

  /**
   * @brief unsets all the shaders that have been set
  */
  virtual void 
  unsetShaders() {}

  /**
   * @brief sets the primitive topology to be used
   * @param  
  */
  virtual void
  setPrimitiveTopology(PRIMITIVE_TOPOLOGY::E /*topology*/){}

  /**
   * @brief loads a .dds if the graphics api can
   * @param path 
   * @return 
  */
  virtual bool
  loadDDS(const Path& path);

  /**
   * @brief initializes everything needed for the window
   * @param window 
  */
  virtual void
  initWindow(void* /*window*/) {}

  virtual Vector2U
  getWindowSize(void* /*window*/);

  virtual void
  setViewport(const Vector2U& /*size*/){}

  virtual void
  resizeSwapChain(const Vector2U& /*size*/){}

  virtual void*
  getDevice() {return nullptr;}

  virtual void*
  getContext() {return nullptr;}

  virtual void
  initTest(){}

  virtual void
  renderTest(){}

 public:

  /**
   * @brief the function for procecing the events
  */
  //void* eventsFunction = nullptr;

  /**
  * @brief the graphical API that has been loaded
  */
  String m_actualGraphicAPI;



 protected:

  friend class Module<GraphicAPI>;
};


}


