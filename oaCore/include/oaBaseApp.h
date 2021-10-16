/**
* @file oaBaseApp.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"


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

 protected:
  
  BaseApp() = default;

 protected:

  friend class Module<BaseApp>;
};

}

