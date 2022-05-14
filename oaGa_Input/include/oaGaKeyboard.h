#pragma once

#include <oaKeyboard.h>

namespace oaEngineSDK{

class GaKeyboard :
  public Keyboard
{
 private:

  uint32 id;

  friend class Ga_Input;
};

}


