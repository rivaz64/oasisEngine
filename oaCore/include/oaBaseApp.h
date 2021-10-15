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
  void
  run();

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

