#pragma once

#include <oaMouse.h>

namespace oaEngineSDK{

class GaMouse :
  public Mouse
{
 public:
  GaMouse(uint32 id);

  bool
	isButtonDown(const BUTTON::E button) override;

  bool
	wasButtonPressed(const BUTTON::E button);

  bool
	wasButtonReleased(const BUTTON::E button);

  float
	getAxis(const AXIS::E axis) override;

 private:

  uint32 m_id;

  friend class GaInput;
};

}


