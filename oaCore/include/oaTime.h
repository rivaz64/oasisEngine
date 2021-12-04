/**
* @file oaTime.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/3/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaModule.h"

namespace oaEngineSDK{

/**
 * @brief the module for everything time related
*/
class OA_CORE_EXPORT Time :
  public Module<Time>
{
 public:

  FORCEINLINE const float&
  getDelta(){
    return deltaTime;
  }

 private:
  
  /**
   * @brief the time passed since the last update
  */
  float deltaTime = 0;

  friend class BaseApp;
};

}


