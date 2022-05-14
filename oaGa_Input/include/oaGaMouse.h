#pragma once

#include <oaMouse.h>

namespace oaEngineSDK{

class GaMouse :
  public Mouse
{
 private:

  uint32 id;

  friend class Ga_Input;
};

}


