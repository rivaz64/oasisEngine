/**
* @file oaBaseApp.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/13/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT BaseApp :
  public Module<BaseApp>
{
 public:

  /**
   * @brief runs the engine
  */
  void
  run();

 protected:
  
  BaseApp() = default;

  friend class Module<BaseApp>;
};

}

