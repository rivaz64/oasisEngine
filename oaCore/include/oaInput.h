/**
* @file oaInput.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>

namespace oaEngineSDK{

/**
 * @brief class for creating things for inputs
*/
class Input :
  public Module<Input>
{
 public:
  
  /**
   * @brief creates the interface for the inputs of a mouse
   * @return 
  */
  virtual uint32
  createDeviceMouse();

  /**
   * @brief creates the interface for the inputs of a keyboard
   * @return 
  */
  virtual uint32
  createDeviceKeyboard();

 private:
  friend class Module<Input>;
};

}


