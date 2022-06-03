#include "oaInputAPI.h"
#include "oaKeyboard.h"
#include "oaMouse.h"

namespace oaEngineSDK{

SPtr<Mouse>
InputAPI::createDeviceMouse()
{
  return makeSPtr<Mouse>();
}

SPtr<Keyboard>
InputAPI::createDeviceKeyboard()
{
  return makeSPtr<Keyboard>();
}

//void 
//Input::mapBool(uint32 inputId, uint32 deviceId, uint32 input)
//{
//}

}