#include "oaInput.h"
#include "oaKeyboard.h"
#include "oaMouse.h"

namespace oaEngineSDK{

SPtr<Mouse>
Input::createDeviceMouse()
{
  return makeSPtr<Mouse>();
}

SPtr<Keyboard>
Input::createDeviceKeyboard()
{
  return makeSPtr<Keyboard>();
}

//void 
//Input::mapBool(uint32 inputId, uint32 deviceId, uint32 input)
//{
//}

}