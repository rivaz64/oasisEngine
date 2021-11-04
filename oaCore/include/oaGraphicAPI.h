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
#include "oaVector4f.h"
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
  events();

  /**
   * @brief compiles the shaders
   * @param folder the folders where the shaders are
   * @return 
  */
  bool
  compileShaders(String folder);

  /**
   * @brief creates a buffer
   * @return 
  */
  virtual SPtr<Buffer> 
  createBuffer();

  /**
  * @brief creates a texture
  * @return 
  */
  virtual SPtr<Texture> 
  createTexture();

  /**
  * @brief sets the color of the background
  * @param color 
  */
  virtual void
  setBackgroundColor(const Vector4f& /*color*/) {}

  /**
  * @brief clears the screen
  */
  virtual void
  clear();

  /**
   * @brief draws to the back buffer
   * @param indexes 
  */
  virtual void
  draw(uint32 /*indexes*/){}

  /**
   * @brief shows the things that where rendered
   * @param indexes number of indexes to draw
  */
  virtual void
  show(){}

  /**
   * @brief sets the vertex bubbers that are going to be drawn
   * @param buffer 
  */
  virtual void
  setVertexBuffer(const SPtr<Buffer>& /*buffer*/){}

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

  virtual void*
  getWindow() { return nullptr; }

  virtual void*
  getDevice() {return nullptr;}

  virtual void*
  getContext() {return nullptr;}

  virtual void
  initImGui(){}

  virtual void
  newImGuiFrame(){}
  void
  ImGuiRender(){}
  virtual void*
  getImGui(){return nullptr;}

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

  /**
   * @brief the vertex shader
  */
  SPtr<Shader> vertexShader;

  /**
  * @brief the pixel shader
  */
  SPtr<Shader> pixelShader;

  friend class Module<GraphicAPI>;
};


}


