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

  /**
   * @brief gets the current delta time
   * @return 
  */
  FORCEINLINE const float&
  getDelta(){
    return m_deltaTime;
  }

  /**
   * @brief returns a string with the actual date and time
   * @return 
  */
  String
  getActualDateAndTime();

  /**
   * @brief gets the number of seconds since the epoch
   * @return 
  */
  uint32
  getTime();

 private:
  /**
   * @brief calculates the new deltaTime
  */
  void
  update();

 private:
  
  /**
   * @brief the time passed since the last update
  */
  float m_deltaTime = 0;

  friend class BaseApp;
};

}



