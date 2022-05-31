#include "oaMouse.h"

namespace oaEngineSDK{

bool
Mouse::isButtonDown(const BUTTON::E key)
{
  return false;
}

bool
Mouse::wasButtonPressed(const BUTTON::E button)
{
  return false;
}

bool 
Mouse::wasButtonReleased(const BUTTON::E button)
{
  return false;
}

float 
Mouse::getAxis(const AXIS::E axis)
{
  return 0.0f;
}

}

