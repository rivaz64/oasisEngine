/**
* @file oaBaseApp.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"
#include "oaVector4f.h"


namespace oaEngineSDK{

/**
 * @brief the base app for the engine
*/
class OA_CORE_EXPORT BaseApp :
  public Module<BaseApp>
{
 public:

  /**
   * @brief runs the engine
  */
  virtual void
  run();

  /**
   * @brief the things to do after the graphics api is started
  */
  virtual void
  postInit();

  /**
   * @brief loads a plugin 
   * @param DLL the dll of the plugin
  */
  virtual void
  loadPlugIn(String DLL);

  /**
   * @brief the game loop
  */
  virtual void
  mainLoop();

  /**
   * @brief render everything to the screen and shows it
  */
  virtual void
  render();

  

 protected:
  
  BaseApp() = default;

 protected:

  /**
   * @brief the frame rate
  */
  float framesPerSecond = 60;

  /**
   * @brief the time a frame is going to be on screen
  */
  float secondPerFrame = 1.f/framesPerSecond;

  /**
   * @brief the time that has pass since the last update
  */
  float deltaTime = 0;


  friend class Module<BaseApp>;
};

}

