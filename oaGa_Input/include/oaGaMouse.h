#pragma once

#include <oaMouse.h>

namespace oaEngineSDK{

class GaMouse :
  public Mouse
{
 private:

  uint32 m_id;

  friend class GaInput;
};

}


