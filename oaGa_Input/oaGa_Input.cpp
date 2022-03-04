#include "oaGa_Input.h"

namespace oaEngineSDK{

uint32 
Ga_Input::createDeviceMouse()
{
  return m_manager.CreateDevice<gainput::InputDeviceMouse>();
}

uint32 
Ga_Input::createDeviceKeyboard()
{
  return m_manager.CreateDevice<gainput::InputDeviceKeyboard>();
}

}

