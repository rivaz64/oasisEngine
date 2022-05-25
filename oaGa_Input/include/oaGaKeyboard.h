#pragma once

#include <oaKeyboard.h>

namespace oaEngineSDK{

class GaKeyboard :
  public Keyboard
{
 public:
  
  GaKeyboard();

  bool
	isKeyDown(const KEY::E key) override;

  //void
  //map(const String& name, const KEY::E key) override;
  
 private:

  uint32 m_id;

  friend class GaInput;
};

}


