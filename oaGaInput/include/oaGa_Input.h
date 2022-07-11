/**
* @file oaGa_Input.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

# define GAINPUT_PLATFORM_WIN

#if defined(GAINPUT_PLATFORM_WIN)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <stdio.h>
#define LOG(...) {char buf[256]; sprintf(buf, __VA_ARGS__); OutputDebugStringA(buf); }
#endif

#pragma once

#include <oaInputAPI.h>
#include <gainput\gainput.h>

namespace oaEngineSDK{

using GaInputManager = gainput::InputManager;
using GaInputMap = gainput::InputMap;

class GaInput :
  public InputAPI
{
 public:

  GaInput();

  void
  init(const Vector2U& size) override;

  void
  update() override;

  SPtr<Mouse>
  createDeviceMouse() override;

  SPtr<Keyboard>
  createDeviceKeyboard() override;

  void
  HandleMessage(const MSG& msg) override;

 private:

  GaInputManager m_manager;

  GaInputMap m_inputMap;

  friend class GaKeyboard;

  friend class GaMouse;
};

}


