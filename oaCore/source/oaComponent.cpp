#include "oaComponent.h"

namespace oaEngineSDK
{
namespace
{
  //Factory<Component> factory;
}
SPtr<Component>
Component::create(uint32 type)
{
  return Factory<Component>::create(type);
}
const Map<uint32, String>& 
Component::getNames()
{
  return Factory<Component>::getNames();
}
}