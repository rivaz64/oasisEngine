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
 * @brief for handling system messages
*/
struct MSG{
  void* HWND;
  uint32 message;
  uint64 wParam;
  int64  lParam;
};

/**
 * @brief class for creating things for inputs
*/
class OA_CORE_EXPORT Input :
  public Module<Input>
{
 public:
  
  virtual void
  init(const Vector2U& size) {}

  virtual void
  update() {}

  /**
   * @brief creates the interface for the inputs of a mouse
   * @return 
  */
  virtual SPtr<Mouse>
  createDeviceMouse();

  /**
   * @brief creates the interface for the inputs of a keyboard
   * @return 
  */
  virtual SPtr<Keyboard>
  createDeviceKeyboard();

  /**
   * @brief handles the message of the sistem
   * @param msg 
  */
  virtual void
  HandleMessage(const MSG& msg) {}

  /**
   * @brief maps an input that can be on and off
  */
  //virtual void
  //mapBool(uint32 inputId,uint32 deviceId, uint32 input);

 private:
  friend class Module<Input>;
};

}


