/**
* @file oaGaMouse.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 5/30/2022
*/


#include "oaGaMouse.h"
#include "oaGaInput.h"

namespace oaEngineSDK{

GaMouse::GaMouse(uint32 id) :
  m_id(id)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  inputMap.MapBool(BUTTON::kLeft, m_id, gainput::MouseButtonLeft);
  inputMap.MapBool(BUTTON::kRight, m_id, gainput::MouseButtonRight);
  inputMap.MapBool(BUTTON::kMiddle, m_id, gainput::MouseButtonMiddle);
  inputMap.MapFloat(AXIS::kX, m_id, gainput::MouseAxisX);
  inputMap.MapFloat(AXIS::kY, m_id, gainput::MouseAxisY);
}

bool
GaMouse::isButtonDown(const BUTTON::E button)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  return inputMap.GetBool(button);
}

bool
GaMouse::wasButtonPressed(const BUTTON::E button)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  return inputMap.GetBoolIsNew(button);
}

bool 
GaMouse::wasButtonReleased(const BUTTON::E button)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  return inputMap.GetBoolWasDown(button);
}

float 
GaMouse::getAxis(const AXIS::E axis)
{
  auto& inputMap = reinterpret_cast<GaInput*>(GaInput::instancePtr())->m_inputMap;
  return inputMap.GetFloatDelta(axis);
}

}

