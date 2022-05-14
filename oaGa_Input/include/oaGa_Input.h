/**
* @file oaInput.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include <oaInput.h>
#include <gainput\gainput.h>

namespace oaEngineSDK{

class Ga_Input :
  public Input
{
 public:

  SPtr<Mouse>
  createDeviceMouse() override;

  SPtr<Keyboard>
  createDeviceKeyboard() override;

 private:
  gainput::InputManager m_manager;
};

}


