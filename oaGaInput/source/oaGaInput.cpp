/**
* @file oaGa_Input.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#include "oaGaInput.h"
#include "oaGaMouse.h"
#include "oaGaKeyboard.h"
#include <Windows.h>
#include <oaVector2U.h>

namespace oaEngineSDK{

GaInput::GaInput() :
  m_manager(), m_inputMap(m_manager)
{
}

void GaInput::init(const Vector2U& size)
{
  m_manager.SetDisplaySize(size.x, size.y);
}

void
GaInput::update()
{
  m_manager.Update();
}

SPtr<Mouse>
GaInput::createDeviceMouse()
{
  auto mouse = makeSPtr<GaMouse>(m_manager.CreateDevice<gainput::InputDeviceMouse>());
  return mouse;
}

SPtr<Keyboard>
GaInput::createDeviceKeyboard()
{
  auto keyboard = makeSPtr<GaKeyboard>(m_manager.CreateDevice<gainput::InputDeviceKeyboard>());
  return keyboard;
}

void 
GaInput::HandleMessage(const MSG& msg)
{
  tagMSG wmsg;
  wmsg.hwnd = reinterpret_cast<HWND>(msg.HWND);
  wmsg.message = msg.message;
  wmsg.wParam = msg.wParam;
  wmsg.lParam = msg.lParam;
  m_manager.HandleMessage(wmsg);
}

}

