/**
* @file oaGraphicAPI.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

/**
 * @brief everything used for graphycs
*/
class OA_CORE_EXPORT GraphicAPI :
  public Module<GraphicAPI>
{
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

 protected:

  GraphicAPI() = default;

  /**
   * @brief the width of the window at the begining
  */
  uint32 windowWidth = 800;

  /**
  * @brief the height of the window at the begining
  */
  uint32 windowHeight = 600;

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


