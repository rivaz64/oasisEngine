#include "oaGa_Input.h"
#include "oaGaMouse.h"
#include "oaGaKeyboard.h"

namespace oaEngineSDK{

SPtr<Mouse>
Ga_Input::createDeviceMouse()
{
  auto mouse = makeSPtr<GaMouse>();
  mouse->id = m_manager.CreateDevice<gainput::InputDeviceMouse>();
  return mouse;
}

SPtr<Keyboard>
Ga_Input::createDeviceKeyboard()
{
  auto keyboard = makeSPtr<GaKeyboard>();
  keyboard->id = m_manager.CreateDevice<gainput::InputDeviceKeyboard>();
  return keyboard;
}

}

