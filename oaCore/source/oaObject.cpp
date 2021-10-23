#include "oaObject.h"
#include "oaGraphicAPI.h"
oaEngineSDK::Object::Object()
{
  location = {0.f,0.f,0.f};
  locationB = GraphicAPI::instancePtr()->createBuffer();
}
